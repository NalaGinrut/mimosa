#ifndef __MIMOSA_KSHELL_H__
#define __MIMOSA_KSHELL_H__
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

#define KSC_DESC_LEN	256
#define KSC_NAME_LEN	64
#define KSC_BUF_SIZE	80	// enough for one VGA text line

extern char principio[], etext[], edata[], recondo[];

typedef int (*ksc_run_t)(int ,char** ,struct Trapframe*);

typedef struct Kernel_Shell_Command
{
  const char name[KSC_NAME_LEN];
  const char desc[KSC_DESC_LEN];

  // return -1 to force kshell to exit
  ksc_run_t run;
}ksc_t;

// Activate the kernel monitor,
// optionally providing a trap frame indicating the current state
// (NULL if none).
void mimosa_kshell_run(struct Trapframe *tf);

// Functions implementing monitor commands.

int get_pgstat(const char *);



#endif // End of __MIMOSA_KSHELL_H__;
