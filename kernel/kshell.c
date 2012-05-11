/*	
 *  Copyright (C) 2012
 *	"Mu Lei" known as "NalaGinrut" <NalaGinrut@gmail.com>
 
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <libkern.h>
#include <error.h>
#include <retval.h>
#include <bsp/bsp_mm.h>
#include <bsp/bsp_io.h>
#include <bsp/bsp_cpu.h>
#include <bsp/pmap.h>
#include <drivers/console.h>
#include <debug.h>
#include <kshell.h>

static int ksc_help(int argc ,char **argv ,struct Trapframe *tf);
static int ksc_kerninfo(int argc ,char **argv ,struct Trapframe *tf);
static int ksc_show_map(int argc, char **argv ,struct Trapframe *tf);
static int ksc_set_pgstat(int argc ,char **argv ,struct Trapframe *tf);
static int ksc_get_pgstat(const char* stat_str);
static int ksc_show_mem(int argc ,char **argv ,struct Trapframe *tf);
#ifdef __KERN_DEBUG__
static int ksc_backtrace(int argc ,char **argv ,struct Trapframe *tf);
#endif

static int run_cmd(char *buf ,struct Trapframe *tf);

static void ksc_error_handler(retval rv ,char *cmd);

static ksc_t kernel_shell_cmd[] =
  {
    { "help" ,"Display this list of commands", ksc_help },
    { "kerninfo" ,"Display information about the kernel", ksc_kerninfo },
#ifdef __KERN_DEBUG__
    { "kern-bt" ,"Kernel backtrace" ,ksc_backtrace },
#endif
    { "show-map" ,"Show memory mappings" ,ksc_show_map },
    { "set-pgstat" ,"Set page status" ,ksc_set_pgstat },
    { "show-mem" ,"Show memory in byte" ,ksc_show_mem },
  };

#define KSC_CNT \
  (sizeof(kernel_shell_cmd)/sizeof(kernel_shell_cmd[0]))

/***** Implementations of basic kernel shell commands *****/

static int ksc_help(int argc ,char **argv ,struct Trapframe *tf)
{
  for(int i = 0; i < KSC_CNT; i++)
    {
      ksc_t ksc = kernel_shell_cmd[i];
      cprintf("%s - %s\n", ksc.name, ksc.desc);
    }
  
  return 0;
}

static int ksc_kerninfo(int argc ,char **argv ,struct Trapframe *tf)
{
  extern char principio[], etext[], edata[], recondo[];

  cprintf("Special kernel symbols:\n");
  cprintf("  principio %08x (virt)  %08x (phys)\n" ,principio ,principio - KERN_BASE);
  cprintf("  etext  %08x (virt)  %08x (phys)\n" ,etext ,etext - KERN_BASE);
  cprintf("  edata  %08x (virt)  %08x (phys)\n" ,edata ,edata - KERN_BASE);
  cprintf("  recondo    %08x (virt)  %08x (phys)\n" ,recondo ,recondo - KERN_BASE);
  cprintf("Kernel executable memory footprint: %dKB\n",
	  (recondo-principio+1023)/1024);

  return 0;
}

#ifdef __KERN_DEBUG__
static int ksc_backtrace(int argc ,char **argv ,struct Trapframe *tf)
{
  // Your code here.
  unsigned int *ptr=(unsigned int *)__get_frame_pointer();
  int ebp=0,eip=1,args=2;
  int count=0;
  struct Eipdebuginfo info;

  cprintf("Stack backtrace:\n");
  while(count<=8)
    {
	  
      if(debuginfo_eip((uintptr_t)ptr[eip] ,&info))
	panic("oh~no!\n");

      // exit while ebp backtrace to 0x0, it's our magic ebp value to the end;
      if(!ptr[ebp])
	panic("backtrace to end!\n");

      cprintf("%s:%u: %s+%x\n" ,info.eip_file ,info.eip_line,
	      info.eip_fn_name ,info.eip_fn_namelen);
      cprintf("ebp %08x eip %x args %08x %08x %08x %08x %08x\n", 
	      ptr ,ptr[eip] ,ptr[args+0], ptr[args+1] ,
	      ptr[args+2] ,ptr[args+3] ,ptr[args+4]);
      ptr=(unsigned int*)ptr[ebp];
      count++;
    }
							
  return 0;
}
#endif

static int ksc_show_mem(int argc ,char **argv ,struct Trapframe *tf)
{
  const char *begin = (char *)strtol(argv[1] ,'\0' ,16);
  const char *end = (char *)strtol(argv[2] ,'\0' ,16);
  pde_t *pd = NULL;
  struct Page *pg = NULL;

  do{
    if( __page_lookup(pmap_get_tmp_pgdir() ,(void*)begin ,&pd) )
      {
	cprintf("%p: %08x\n" ,begin ,*begin);
      }
    else
      {
	cprintf("%p: is not mapped!\n",begin);
      }

    begin++;

  }while( begin <= end );

  return 0;
}


static int ksc_get_pgstat(const char* stat_str)
{
  char *stats[8] = 
    { "PTE_P" ,"PTE_W" ,"PTE_U" ,"PTE_PWT",
      "PTE_PCD" ,"PTE_A" ,"PTE_D" ,"PTE_PS"
    };
  int i = 0;
    
  while( strncmp(stat_str ,stats[i] ,7) )
    i++;

  return (i<7&&i>=0)? i : -1;
}

static int ksc_set_pgstat(int argc ,char **argv ,struct Trapframe *tf)
{
  int st_idx = 0;
  void *begin = (void *)strtol(argv[1],'\0',16);
  void *end = NULL;
  pde_t *pd = NULL;
  struct Page *pg = NULL;
  physaddr_t paddr = 0;
  int flag = 0;
  int i = 0;
  char *stats[20] = 
    { "present" ,"writable" ,"user" ,"write-through",
      "cache-disable" ,"accessed" ,"dirty" ,"pagesize-ex"
    };

  // just one address mode
  if( argc < 4 )
    {
      end = begin;
      st_idx = 2;
    }
  else // address range mode
    {
      end = (void*)strtol(argv[2] ,'\0' ,16);
      st_idx = 3;
    }

  do{
    begin = (void*)ROUND_DOWN((u32_t)begin ,PG_SIZE);
    // find vaddr's map
    pg = __page_lookup(__boot_pgdir ,begin ,&pd);
    flag = pg? 1 : 0;
    
    if( flag )
      {
	pd = (pte_t*)KADDR(PTA(*pd));
	paddr = pd[PTX(begin)];
	  
	cprintf("%p:  ==> %p\n mapped?:%s\n",
		begin ,(void*)ROUND_DOWN(paddr ,PG_SIZE) ,flag?"yes":"no");
	  
	// modify status
	for(i=st_idx ;i<argc ;i++)
	  {
	    int st = ksc_get_pgstat(argv[i]);
	    cprintf("get st:%d\n",st);
	    
	    if( st < 0 )
	      {
		cprintf("invalid stat: %s",argv[i]);
		return -1;
	      }
	    
	    pd[PTX(begin)] = ((pte_t)((u32_t)pd[PTX(begin)]
				      | (1<<st)));
	    cprintf("after: pt[PTX(begin)]=%p\n",pd[PTX(begin)]);
	  }
	
	paddr = pd[PTX(begin)];
	//print current status
	cprintf("now stats: ");
	
	for(i=0 ;i<=7 ;i++)
	  cprintf("%s ",(paddr>>i)&0x1?stats[i]:"");

	cprintf("\n");
      }else
      {
	paddr = 0xBADBADAD;
	cprintf("%p:  ==> %p\n mapped?:%s\n",
		begin ,(void*)paddr ,flag?"yes":"no");
      }

    begin += 0x1000;
  }while( begin <= end );

  return 0;
}

static int ksc_show_map(int argc ,char **argv ,struct Trapframe *tf)
{
  if( argc < 3) 
    {
      cprintf("usage: show-map begin end\n");
      return -1;
    }

  void *begin = (void *)strtol(argv[1] ,'\0' ,16);
  void *end = (void *)strtol(argv[2] ,'\0' ,16);
  struct Page *pg = NULL;
  pte_t *pt = NULL;
  physaddr_t paddr = 0;
  char *stats[20] = 
    { "present" ,"writable" ,"user" ,"write-through",
      "cache-disable" ,"accessed" ,"dirty" ,"pagesize-ex"
    };

  do{
    begin = (void*)ROUND_DOWN((u32_t)begin ,PG_SIZE);
    pg = __page_lookup(__boot_pgdir ,begin ,&pt);
      
    if( pg )
      {
	pt = (pte_t*)KADDR(PTA(*pt));
	paddr = pt[PTX(begin)];
	  
	cprintf("%p:  ==> %p\n mapped?:%s\n",
		begin ,(void*)ROUND_DOWN(paddr ,PG_SIZE)
		,pg?"yes":"no");

	cprintf("stats: ");

	for(int i=0 ;i<=7 ;i++)
	  cprintf("%s ",(paddr>>i)&0x1?stats[i]:"");

	cprintf("\n");
      }
    else
      {
	paddr = 0xBADBADAD;
	cprintf("%p:  ==> %p\n mapped?:%s\n",
		begin ,(void*)paddr ,pg?"yes":"no");
      }

    begin += 0x1000;
  }while( begin <= end );

  return 0;
}


/***** Kernel shell command interpreter *****/

#define KSC_WHITESPACE "\t\r\n "
#define KSC_MAXARGS 16

static int run_cmd(char *buf ,struct Trapframe *tf)
{
  int argc;
  char *argv[KSC_MAXARGS];
  int i;

  // Parse the command buffer into whitespace-separated arguments
  argc = 0;
  argv[argc] = NULL;
  
  while(1)
    {
      // gobble whitespace
      while(*buf && strchr(KSC_WHITESPACE ,*buf))
	*buf++ = 0;

      if(0 == *buf)
	break;

      // save and scan past next arg
      if(KSC_MAXARGS-1 == argc)
	{
	  cprintf("Too many arguments (max %d)\n", KSC_MAXARGS);
	  return 0;
	}
    
    argv[argc++] = buf;
    
    while(*buf && !strchr(KSC_WHITESPACE ,*buf))
      buf++;
  }
  
  argv[argc] = 0;

  // Lookup and invoke the command
  if(0 == argc)
    return 0;

  for (i = 0 ;i < KSC_CNT ;i++)
    {
      if(0 == strncmp(argv[0] ,kernel_shell_cmd[i].name ,KSC_NAME_LEN))
	return kernel_shell_cmd[i].run(argc ,argv ,tf);
    }
  cprintf("Unknown command '%s'\n", argv[0]);
  return 0;
}

void mimosa_kshell_run(struct Trapframe *tf)
{
  char *cmd;
  retval rv;

  cprintf("Welcome to the Mimosa kernel shell!\n");
  cprintf("Type 'help' for a list of commands.\n");

  while(1)
    {
      cmd = read_line("K> ");

      if(NULL != cmd && (rv = run_cmd(cmd ,tf)) < 0)
	{
	  /* TODO: use error handler to catch retval
	   *       1. invalid cmd will throw exception
	   *       2. exit ksc mode and call regular mode
	   *	   3. restart/shutdown
	   */
	  ksc_error_handler(rv ,cmd);
	  break;
	}
    }
}

static void ksc_error_handler(retval rv ,char *cmd)
{
  cprintf("retval:%d\n,cmd:%s\n,len-cmd:%d\n",
	  rv ,cmd ,strnlen(cmd ,KSC_BUF_SIZE));
}

