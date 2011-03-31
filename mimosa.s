
mimosa:     file format elf32-i386


Disassembly of section .text:

c0100000 <multiboot_header>:
c0100000:	02 b0 ad 1b 03 00    	add    0x31bad(%eax),%dh
c0100006:	00 00                	add    %al,(%eax)
c0100008:	fb                   	sti    
c0100009:	4f                   	dec    %edi
c010000a:	52                   	push   %edx
c010000b:	e4 66                	in     $0x66,%al

c010000c <_start>:
c010000c:	66 c7 05 72 04 00 00 	movw   $0x1234,0x472
c0100013:	34 12 
c0100015:	e8 00 00 00 00       	call   c010001a <set_gdt>

c010001a <set_gdt>:
c010001a:	0f 01 15 00 50 10 00 	lgdtl  0x105000
c0100021:	66 b8 10 00          	mov    $0x10,%ax
c0100025:	8e d8                	mov    %eax,%ds
c0100027:	8e c0                	mov    %eax,%es
c0100029:	8e d0                	mov    %eax,%ss
c010002b:	ea 32 00 10 c0 08 00 	ljmp   $0x8,$0xc0100032

c0100032 <set_cee_env>:
c0100032:	bd 00 00 00 00       	mov    $0x0,%ebp
c0100037:	bc 00 50 10 c0       	mov    $0xc0105000,%esp
c010003c:	e8 07 00 00 00       	call   c0100048 <platform_init>

c0100041 <return_is_error>:
c0100041:	e8 76 0a 00 00       	call   c0100abc <kern_debug>
	...

c0100048 <platform_init>:
c0100048:	55                   	push   %ebp
c0100049:	89 e5                	mov    %esp,%ebp
c010004b:	83 ec 18             	sub    $0x18,%esp
c010004e:	c7 04 24 00 10 10 c0 	movl   $0xc0101000,(%esp)
c0100055:	e8 0a 0a 00 00       	call   c0100a64 <msg_print>
c010005a:	c9                   	leave  
c010005b:	c3                   	ret    

c010005c <bsp_init_clear_tmp>:
c010005c:	55                   	push   %ebp
c010005d:	89 e5                	mov    %esp,%ebp
c010005f:	83 ec 18             	sub    $0x18,%esp
c0100062:	ba cc 57 10 c0       	mov    $0xc01057cc,%edx
c0100067:	b8 a0 55 10 c0       	mov    $0xc01055a0,%eax
c010006c:	89 d1                	mov    %edx,%ecx
c010006e:	29 c1                	sub    %eax,%ecx
c0100070:	89 c8                	mov    %ecx,%eax
c0100072:	89 44 24 08          	mov    %eax,0x8(%esp)
c0100076:	c7 44 24 04 00 00 00 	movl   $0x0,0x4(%esp)
c010007d:	00 
c010007e:	c7 04 24 a0 55 10 c0 	movl   $0xc01055a0,(%esp)
c0100085:	e8 62 09 00 00       	call   c01009ec <memset>
c010008a:	c9                   	leave  
c010008b:	c3                   	ret    

c010008c <bsp_init_console>:
c010008c:	55                   	push   %ebp
c010008d:	89 e5                	mov    %esp,%ebp
c010008f:	5d                   	pop    %ebp
c0100090:	c3                   	ret    

c0100091 <bsp_init_online_debug>:
c0100091:	55                   	push   %ebp
c0100092:	89 e5                	mov    %esp,%ebp
c0100094:	5d                   	pop    %ebp
c0100095:	c3                   	ret    

c0100096 <bsp_init_memory>:
c0100096:	55                   	push   %ebp
c0100097:	89 e5                	mov    %esp,%ebp
c0100099:	5d                   	pop    %ebp
c010009a:	c3                   	ret    
c010009b:	90                   	nop

c010009c <console_init>:
c010009c:	55                   	push   %ebp
c010009d:	89 e5                	mov    %esp,%ebp
c010009f:	83 ec 08             	sub    $0x8,%esp
c01000a2:	e8 22 00 00 00       	call   c01000c9 <cga_init>
c01000a7:	e8 4a 04 00 00       	call   c01004f6 <kbd_init>
c01000ac:	c9                   	leave  
c01000ad:	c3                   	ret    

c01000ae <console_putc>:
c01000ae:	55                   	push   %ebp
c01000af:	89 e5                	mov    %esp,%ebp
c01000b1:	83 ec 28             	sub    $0x28,%esp
c01000b4:	8b 45 08             	mov    0x8(%ebp),%eax
c01000b7:	66 89 45 f4          	mov    %ax,-0xc(%ebp)
c01000bb:	0f b7 45 f4          	movzwl -0xc(%ebp),%eax
c01000bf:	89 04 24             	mov    %eax,(%esp)
c01000c2:	e8 de 00 00 00       	call   c01001a5 <cga_putc>
c01000c7:	c9                   	leave  
c01000c8:	c3                   	ret    

c01000c9 <cga_init>:
c01000c9:	55                   	push   %ebp
c01000ca:	89 e5                	mov    %esp,%ebp
c01000cc:	83 ec 20             	sub    $0x20,%esp
c01000cf:	b8 00 80 1b c0       	mov    $0xc01b8000,%eax
c01000d4:	0f b7 00             	movzwl (%eax),%eax
c01000d7:	66 89 45 fa          	mov    %ax,-0x6(%ebp)
c01000db:	b8 00 80 1b c0       	mov    $0xc01b8000,%eax
c01000e0:	66 c7 00 5a a5       	movw   $0xa55a,(%eax)
c01000e5:	b8 00 80 1b c0       	mov    $0xc01b8000,%eax
c01000ea:	0f b7 00             	movzwl (%eax),%eax
c01000ed:	66 3d 5a a5          	cmp    $0xa55a,%ax
c01000f1:	75 07                	jne    c01000fa <cga_init+0x31>
c01000f3:	b8 d4 03 00 00       	mov    $0x3d4,%eax
c01000f8:	eb 05                	jmp    c01000ff <cga_init+0x36>
c01000fa:	b8 b4 03 00 00       	mov    $0x3b4,%eax
c01000ff:	a3 a0 55 10 c0       	mov    %eax,0xc01055a0
c0100104:	b8 00 80 1b c0       	mov    $0xc01b8000,%eax
c0100109:	0f b7 55 fa          	movzwl -0x6(%ebp),%edx
c010010d:	66 89 10             	mov    %dx,(%eax)
c0100110:	a1 a0 55 10 c0       	mov    0xc01055a0,%eax
c0100115:	3d b4 03 00 00       	cmp    $0x3b4,%eax
c010011a:	75 07                	jne    c0100123 <cga_init+0x5a>
c010011c:	b8 00 00 1b c0       	mov    $0xc01b0000,%eax
c0100121:	eb 05                	jmp    c0100128 <cga_init+0x5f>
c0100123:	b8 00 80 1b c0       	mov    $0xc01b8000,%eax
c0100128:	a3 a4 55 10 c0       	mov    %eax,0xc01055a4
c010012d:	a1 a0 55 10 c0       	mov    0xc01055a0,%eax
c0100132:	89 45 f4             	mov    %eax,-0xc(%ebp)
c0100135:	c6 45 ff 0e          	movb   $0xe,-0x1(%ebp)
c0100139:	0f b6 45 ff          	movzbl -0x1(%ebp),%eax
c010013d:	8b 55 f4             	mov    -0xc(%ebp),%edx
c0100140:	ee                   	out    %al,(%dx)
c0100141:	a1 a0 55 10 c0       	mov    0xc01055a0,%eax
c0100146:	83 c0 01             	add    $0x1,%eax
c0100149:	89 45 f0             	mov    %eax,-0x10(%ebp)
c010014c:	8b 45 f0             	mov    -0x10(%ebp),%eax
c010014f:	89 c2                	mov    %eax,%edx
c0100151:	ec                   	in     (%dx),%al
c0100152:	88 45 fe             	mov    %al,-0x2(%ebp)
c0100155:	0f b6 45 fe          	movzbl -0x2(%ebp),%eax
c0100159:	0f b6 c0             	movzbl %al,%eax
c010015c:	c1 e0 08             	shl    $0x8,%eax
c010015f:	66 a3 a8 55 10 c0    	mov    %ax,0xc01055a8
c0100165:	a1 a0 55 10 c0       	mov    0xc01055a0,%eax
c010016a:	89 45 ec             	mov    %eax,-0x14(%ebp)
c010016d:	c6 45 fd 0f          	movb   $0xf,-0x3(%ebp)
c0100171:	0f b6 45 fd          	movzbl -0x3(%ebp),%eax
c0100175:	8b 55 ec             	mov    -0x14(%ebp),%edx
c0100178:	ee                   	out    %al,(%dx)
c0100179:	a1 a0 55 10 c0       	mov    0xc01055a0,%eax
c010017e:	83 c0 01             	add    $0x1,%eax
c0100181:	89 45 e8             	mov    %eax,-0x18(%ebp)
c0100184:	8b 45 e8             	mov    -0x18(%ebp),%eax
c0100187:	89 c2                	mov    %eax,%edx
c0100189:	ec                   	in     (%dx),%al
c010018a:	88 45 fc             	mov    %al,-0x4(%ebp)
c010018d:	0f b6 45 fc          	movzbl -0x4(%ebp),%eax
c0100191:	0f b6 d0             	movzbl %al,%edx
c0100194:	0f b7 05 a8 55 10 c0 	movzwl 0xc01055a8,%eax
c010019b:	09 d0                	or     %edx,%eax
c010019d:	66 a3 a8 55 10 c0    	mov    %ax,0xc01055a8
c01001a3:	c9                   	leave  
c01001a4:	c3                   	ret    

c01001a5 <cga_putc>:
c01001a5:	55                   	push   %ebp
c01001a6:	89 e5                	mov    %esp,%ebp
c01001a8:	53                   	push   %ebx
c01001a9:	83 ec 44             	sub    $0x44,%esp
c01001ac:	8b 45 08             	mov    0x8(%ebp),%eax
c01001af:	66 89 45 d4          	mov    %ax,-0x2c(%ebp)
c01001b3:	0f b7 45 d4          	movzwl -0x2c(%ebp),%eax
c01001b7:	25 00 ff 00 00       	and    $0xff00,%eax
c01001bc:	85 c0                	test   %eax,%eax
c01001be:	75 09                	jne    c01001c9 <cga_putc+0x24>
c01001c0:	0f b7 45 d4          	movzwl -0x2c(%ebp),%eax
c01001c4:	80 cc 07             	or     $0x7,%ah
c01001c7:	eb 04                	jmp    c01001cd <cga_putc+0x28>
c01001c9:	0f b7 45 d4          	movzwl -0x2c(%ebp),%eax
c01001cd:	66 89 45 d4          	mov    %ax,-0x2c(%ebp)
c01001d1:	0f b7 45 d4          	movzwl -0x2c(%ebp),%eax
c01001d5:	25 ff 00 00 00       	and    $0xff,%eax
c01001da:	83 f8 09             	cmp    $0x9,%eax
c01001dd:	0f 84 b2 00 00 00    	je     c0100295 <cga_putc+0xf0>
c01001e3:	83 f8 09             	cmp    $0x9,%eax
c01001e6:	7f 0a                	jg     c01001f2 <cga_putc+0x4d>
c01001e8:	83 f8 08             	cmp    $0x8,%eax
c01001eb:	74 14                	je     c0100201 <cga_putc+0x5c>
c01001ed:	e9 d5 00 00 00       	jmp    c01002c7 <cga_putc+0x122>
c01001f2:	83 f8 0a             	cmp    $0xa,%eax
c01001f5:	74 4f                	je     c0100246 <cga_putc+0xa1>
c01001f7:	83 f8 0d             	cmp    $0xd,%eax
c01001fa:	74 5f                	je     c010025b <cga_putc+0xb6>
c01001fc:	e9 c6 00 00 00       	jmp    c01002c7 <cga_putc+0x122>
c0100201:	0f b7 05 a8 55 10 c0 	movzwl 0xc01055a8,%eax
c0100208:	66 85 c0             	test   %ax,%ax
c010020b:	0f 84 dd 00 00 00    	je     c01002ee <cga_putc+0x149>
c0100211:	0f b7 05 a8 55 10 c0 	movzwl 0xc01055a8,%eax
c0100218:	83 e8 01             	sub    $0x1,%eax
c010021b:	66 a3 a8 55 10 c0    	mov    %ax,0xc01055a8
c0100221:	a1 a4 55 10 c0       	mov    0xc01055a4,%eax
c0100226:	0f b7 15 a8 55 10 c0 	movzwl 0xc01055a8,%edx
c010022d:	0f b7 d2             	movzwl %dx,%edx
c0100230:	01 d2                	add    %edx,%edx
c0100232:	8d 14 10             	lea    (%eax,%edx,1),%edx
c0100235:	0f b7 45 d4          	movzwl -0x2c(%ebp),%eax
c0100239:	b0 00                	mov    $0x0,%al
c010023b:	83 c8 20             	or     $0x20,%eax
c010023e:	66 89 02             	mov    %ax,(%edx)
c0100241:	e9 a9 00 00 00       	jmp    c01002ef <cga_putc+0x14a>
c0100246:	0f b7 05 a8 55 10 c0 	movzwl 0xc01055a8,%eax
c010024d:	83 c0 50             	add    $0x50,%eax
c0100250:	66 a3 a8 55 10 c0    	mov    %ax,0xc01055a8
c0100256:	e9 94 00 00 00       	jmp    c01002ef <cga_putc+0x14a>
c010025b:	0f b7 1d a8 55 10 c0 	movzwl 0xc01055a8,%ebx
c0100262:	0f b7 0d a8 55 10 c0 	movzwl 0xc01055a8,%ecx
c0100269:	0f b7 c1             	movzwl %cx,%eax
c010026c:	69 c0 cd cc 00 00    	imul   $0xcccd,%eax,%eax
c0100272:	c1 e8 10             	shr    $0x10,%eax
c0100275:	89 c2                	mov    %eax,%edx
c0100277:	66 c1 ea 06          	shr    $0x6,%dx
c010027b:	89 d0                	mov    %edx,%eax
c010027d:	c1 e0 02             	shl    $0x2,%eax
c0100280:	01 d0                	add    %edx,%eax
c0100282:	c1 e0 04             	shl    $0x4,%eax
c0100285:	89 ca                	mov    %ecx,%edx
c0100287:	66 29 c2             	sub    %ax,%dx
c010028a:	89 d8                	mov    %ebx,%eax
c010028c:	66 29 d0             	sub    %dx,%ax
c010028f:	66 a3 a8 55 10 c0    	mov    %ax,0xc01055a8
c0100295:	c7 04 24 20 00 00 00 	movl   $0x20,(%esp)
c010029c:	e8 0d fe ff ff       	call   c01000ae <console_putc>
c01002a1:	c7 04 24 20 00 00 00 	movl   $0x20,(%esp)
c01002a8:	e8 01 fe ff ff       	call   c01000ae <console_putc>
c01002ad:	c7 04 24 20 00 00 00 	movl   $0x20,(%esp)
c01002b4:	e8 f5 fd ff ff       	call   c01000ae <console_putc>
c01002b9:	c7 04 24 20 00 00 00 	movl   $0x20,(%esp)
c01002c0:	e8 e9 fd ff ff       	call   c01000ae <console_putc>
c01002c5:	eb 28                	jmp    c01002ef <cga_putc+0x14a>
c01002c7:	8b 15 a4 55 10 c0    	mov    0xc01055a4,%edx
c01002cd:	0f b7 05 a8 55 10 c0 	movzwl 0xc01055a8,%eax
c01002d4:	0f b7 c8             	movzwl %ax,%ecx
c01002d7:	01 c9                	add    %ecx,%ecx
c01002d9:	8d 0c 0a             	lea    (%edx,%ecx,1),%ecx
c01002dc:	0f b7 55 d4          	movzwl -0x2c(%ebp),%edx
c01002e0:	66 89 11             	mov    %dx,(%ecx)
c01002e3:	83 c0 01             	add    $0x1,%eax
c01002e6:	66 a3 a8 55 10 c0    	mov    %ax,0xc01055a8
c01002ec:	eb 01                	jmp    c01002ef <cga_putc+0x14a>
c01002ee:	90                   	nop
c01002ef:	a1 a0 55 10 c0       	mov    0xc01055a0,%eax
c01002f4:	89 45 f0             	mov    %eax,-0x10(%ebp)
c01002f7:	c6 45 f7 0e          	movb   $0xe,-0x9(%ebp)
c01002fb:	0f b6 45 f7          	movzbl -0x9(%ebp),%eax
c01002ff:	8b 55 f0             	mov    -0x10(%ebp),%edx
c0100302:	ee                   	out    %al,(%dx)
c0100303:	0f b7 05 a8 55 10 c0 	movzwl 0xc01055a8,%eax
c010030a:	66 c1 e8 08          	shr    $0x8,%ax
c010030e:	0f b6 c0             	movzbl %al,%eax
c0100311:	8b 15 a0 55 10 c0    	mov    0xc01055a0,%edx
c0100317:	83 c2 01             	add    $0x1,%edx
c010031a:	89 55 ec             	mov    %edx,-0x14(%ebp)
c010031d:	88 45 f6             	mov    %al,-0xa(%ebp)
c0100320:	0f b6 45 f6          	movzbl -0xa(%ebp),%eax
c0100324:	8b 55 ec             	mov    -0x14(%ebp),%edx
c0100327:	ee                   	out    %al,(%dx)
c0100328:	a1 a0 55 10 c0       	mov    0xc01055a0,%eax
c010032d:	89 45 e8             	mov    %eax,-0x18(%ebp)
c0100330:	c6 45 f5 0f          	movb   $0xf,-0xb(%ebp)
c0100334:	0f b6 45 f5          	movzbl -0xb(%ebp),%eax
c0100338:	8b 55 e8             	mov    -0x18(%ebp),%edx
c010033b:	ee                   	out    %al,(%dx)
c010033c:	0f b7 05 a8 55 10 c0 	movzwl 0xc01055a8,%eax
c0100343:	0f b6 c0             	movzbl %al,%eax
c0100346:	8b 15 a0 55 10 c0    	mov    0xc01055a0,%edx
c010034c:	83 c2 01             	add    $0x1,%edx
c010034f:	89 55 e4             	mov    %edx,-0x1c(%ebp)
c0100352:	88 45 f4             	mov    %al,-0xc(%ebp)
c0100355:	0f b6 45 f4          	movzbl -0xc(%ebp),%eax
c0100359:	8b 55 e4             	mov    -0x1c(%ebp),%edx
c010035c:	ee                   	out    %al,(%dx)
c010035d:	83 c4 44             	add    $0x44,%esp
c0100360:	5b                   	pop    %ebx
c0100361:	5d                   	pop    %ebp
c0100362:	c3                   	ret    
c0100363:	90                   	nop

c0100364 <kbd_proc_data>:
c0100364:	55                   	push   %ebp
c0100365:	89 e5                	mov    %esp,%ebp
c0100367:	83 ec 20             	sub    $0x20,%esp
c010036a:	c7 45 f4 64 00 00 00 	movl   $0x64,-0xc(%ebp)
c0100371:	8b 45 f4             	mov    -0xc(%ebp),%eax
c0100374:	89 c2                	mov    %eax,%edx
c0100376:	ec                   	in     (%dx),%al
c0100377:	88 45 fe             	mov    %al,-0x2(%ebp)
c010037a:	0f b6 45 fe          	movzbl -0x2(%ebp),%eax
c010037e:	0f b6 c0             	movzbl %al,%eax
c0100381:	83 e0 01             	and    $0x1,%eax
c0100384:	85 c0                	test   %eax,%eax
c0100386:	75 0a                	jne    c0100392 <kbd_proc_data+0x2e>
c0100388:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
c010038d:	e9 4e 01 00 00       	jmp    c01004e0 <kbd_proc_data+0x17c>
c0100392:	c7 45 f0 60 00 00 00 	movl   $0x60,-0x10(%ebp)
c0100399:	8b 45 f0             	mov    -0x10(%ebp),%eax
c010039c:	89 c2                	mov    %eax,%edx
c010039e:	ec                   	in     (%dx),%al
c010039f:	88 45 fd             	mov    %al,-0x3(%ebp)
c01003a2:	0f b6 45 fd          	movzbl -0x3(%ebp),%eax
c01003a6:	88 45 ff             	mov    %al,-0x1(%ebp)
c01003a9:	80 7d ff e0          	cmpb   $0xe0,-0x1(%ebp)
c01003ad:	75 17                	jne    c01003c6 <kbd_proc_data+0x62>
c01003af:	a1 c8 57 10 c0       	mov    0xc01057c8,%eax
c01003b4:	83 c8 40             	or     $0x40,%eax
c01003b7:	a3 c8 57 10 c0       	mov    %eax,0xc01057c8
c01003bc:	b8 00 00 00 00       	mov    $0x0,%eax
c01003c1:	e9 1a 01 00 00       	jmp    c01004e0 <kbd_proc_data+0x17c>
c01003c6:	0f b6 45 ff          	movzbl -0x1(%ebp),%eax
c01003ca:	84 c0                	test   %al,%al
c01003cc:	79 47                	jns    c0100415 <kbd_proc_data+0xb1>
c01003ce:	a1 c8 57 10 c0       	mov    0xc01057c8,%eax
c01003d3:	83 e0 40             	and    $0x40,%eax
c01003d6:	85 c0                	test   %eax,%eax
c01003d8:	75 09                	jne    c01003e3 <kbd_proc_data+0x7f>
c01003da:	0f b6 45 ff          	movzbl -0x1(%ebp),%eax
c01003de:	83 e0 7f             	and    $0x7f,%eax
c01003e1:	eb 04                	jmp    c01003e7 <kbd_proc_data+0x83>
c01003e3:	0f b6 45 ff          	movzbl -0x1(%ebp),%eax
c01003e7:	88 45 ff             	mov    %al,-0x1(%ebp)
c01003ea:	0f b6 45 ff          	movzbl -0x1(%ebp),%eax
c01003ee:	0f b6 80 20 50 10 c0 	movzbl -0x3fefafe0(%eax),%eax
c01003f5:	83 c8 40             	or     $0x40,%eax
c01003f8:	0f b6 c0             	movzbl %al,%eax
c01003fb:	f7 d0                	not    %eax
c01003fd:	89 c2                	mov    %eax,%edx
c01003ff:	a1 c8 57 10 c0       	mov    0xc01057c8,%eax
c0100404:	21 d0                	and    %edx,%eax
c0100406:	a3 c8 57 10 c0       	mov    %eax,0xc01057c8
c010040b:	b8 00 00 00 00       	mov    $0x0,%eax
c0100410:	e9 cb 00 00 00       	jmp    c01004e0 <kbd_proc_data+0x17c>
c0100415:	a1 c8 57 10 c0       	mov    0xc01057c8,%eax
c010041a:	83 e0 40             	and    $0x40,%eax
c010041d:	85 c0                	test   %eax,%eax
c010041f:	74 11                	je     c0100432 <kbd_proc_data+0xce>
c0100421:	80 4d ff 80          	orb    $0x80,-0x1(%ebp)
c0100425:	a1 c8 57 10 c0       	mov    0xc01057c8,%eax
c010042a:	83 e0 bf             	and    $0xffffffbf,%eax
c010042d:	a3 c8 57 10 c0       	mov    %eax,0xc01057c8
c0100432:	0f b6 45 ff          	movzbl -0x1(%ebp),%eax
c0100436:	0f b6 80 20 50 10 c0 	movzbl -0x3fefafe0(%eax),%eax
c010043d:	0f b6 d0             	movzbl %al,%edx
c0100440:	a1 c8 57 10 c0       	mov    0xc01057c8,%eax
c0100445:	09 d0                	or     %edx,%eax
c0100447:	a3 c8 57 10 c0       	mov    %eax,0xc01057c8
c010044c:	0f b6 45 ff          	movzbl -0x1(%ebp),%eax
c0100450:	0f b6 80 20 51 10 c0 	movzbl -0x3fefaee0(%eax),%eax
c0100457:	0f b6 d0             	movzbl %al,%edx
c010045a:	a1 c8 57 10 c0       	mov    0xc01057c8,%eax
c010045f:	31 d0                	xor    %edx,%eax
c0100461:	a3 c8 57 10 c0       	mov    %eax,0xc01057c8
c0100466:	a1 c8 57 10 c0       	mov    0xc01057c8,%eax
c010046b:	83 e0 03             	and    $0x3,%eax
c010046e:	8b 14 85 20 55 10 c0 	mov    -0x3fefaae0(,%eax,4),%edx
c0100475:	0f b6 45 ff          	movzbl -0x1(%ebp),%eax
c0100479:	8d 04 02             	lea    (%edx,%eax,1),%eax
c010047c:	0f b6 00             	movzbl (%eax),%eax
c010047f:	0f b6 c0             	movzbl %al,%eax
c0100482:	89 45 f8             	mov    %eax,-0x8(%ebp)
c0100485:	a1 c8 57 10 c0       	mov    0xc01057c8,%eax
c010048a:	83 e0 08             	and    $0x8,%eax
c010048d:	85 c0                	test   %eax,%eax
c010048f:	74 22                	je     c01004b3 <kbd_proc_data+0x14f>
c0100491:	83 7d f8 60          	cmpl   $0x60,-0x8(%ebp)
c0100495:	7e 0c                	jle    c01004a3 <kbd_proc_data+0x13f>
c0100497:	83 7d f8 7a          	cmpl   $0x7a,-0x8(%ebp)
c010049b:	7f 06                	jg     c01004a3 <kbd_proc_data+0x13f>
c010049d:	83 6d f8 20          	subl   $0x20,-0x8(%ebp)
c01004a1:	eb 10                	jmp    c01004b3 <kbd_proc_data+0x14f>
c01004a3:	83 7d f8 40          	cmpl   $0x40,-0x8(%ebp)
c01004a7:	7e 0a                	jle    c01004b3 <kbd_proc_data+0x14f>
c01004a9:	83 7d f8 5a          	cmpl   $0x5a,-0x8(%ebp)
c01004ad:	7f 04                	jg     c01004b3 <kbd_proc_data+0x14f>
c01004af:	83 45 f8 20          	addl   $0x20,-0x8(%ebp)
c01004b3:	a1 c8 57 10 c0       	mov    0xc01057c8,%eax
c01004b8:	f7 d0                	not    %eax
c01004ba:	83 e0 06             	and    $0x6,%eax
c01004bd:	85 c0                	test   %eax,%eax
c01004bf:	75 1c                	jne    c01004dd <kbd_proc_data+0x179>
c01004c1:	81 7d f8 e9 00 00 00 	cmpl   $0xe9,-0x8(%ebp)
c01004c8:	75 13                	jne    c01004dd <kbd_proc_data+0x179>
c01004ca:	c7 45 ec 92 00 00 00 	movl   $0x92,-0x14(%ebp)
c01004d1:	c6 45 fc 03          	movb   $0x3,-0x4(%ebp)
c01004d5:	0f b6 45 fc          	movzbl -0x4(%ebp),%eax
c01004d9:	8b 55 ec             	mov    -0x14(%ebp),%edx
c01004dc:	ee                   	out    %al,(%dx)
c01004dd:	8b 45 f8             	mov    -0x8(%ebp),%eax
c01004e0:	c9                   	leave  
c01004e1:	c3                   	ret    

c01004e2 <kbd_intr>:
c01004e2:	55                   	push   %ebp
c01004e3:	89 e5                	mov    %esp,%ebp
c01004e5:	83 ec 18             	sub    $0x18,%esp
c01004e8:	c7 04 24 64 03 10 c0 	movl   $0xc0100364,(%esp)
c01004ef:	e8 07 00 00 00       	call   c01004fb <cons_intr>
c01004f4:	c9                   	leave  
c01004f5:	c3                   	ret    

c01004f6 <kbd_init>:
c01004f6:	55                   	push   %ebp
c01004f7:	89 e5                	mov    %esp,%ebp
c01004f9:	5d                   	pop    %ebp
c01004fa:	c3                   	ret    

c01004fb <cons_intr>:
c01004fb:	55                   	push   %ebp
c01004fc:	89 e5                	mov    %esp,%ebp
c01004fe:	83 ec 18             	sub    $0x18,%esp
c0100501:	eb 35                	jmp    c0100538 <cons_intr+0x3d>
c0100503:	83 7d f4 00          	cmpl   $0x0,-0xc(%ebp)
c0100507:	74 2e                	je     c0100537 <cons_intr+0x3c>
c0100509:	a1 c4 57 10 c0       	mov    0xc01057c4,%eax
c010050e:	8b 55 f4             	mov    -0xc(%ebp),%edx
c0100511:	88 90 c0 55 10 c0    	mov    %dl,-0x3fefaa40(%eax)
c0100517:	83 c0 01             	add    $0x1,%eax
c010051a:	a3 c4 57 10 c0       	mov    %eax,0xc01057c4
c010051f:	a1 c4 57 10 c0       	mov    0xc01057c4,%eax
c0100524:	3d 00 02 00 00       	cmp    $0x200,%eax
c0100529:	75 0d                	jne    c0100538 <cons_intr+0x3d>
c010052b:	c7 05 c4 57 10 c0 00 	movl   $0x0,0xc01057c4
c0100532:	00 00 00 
c0100535:	eb 01                	jmp    c0100538 <cons_intr+0x3d>
c0100537:	90                   	nop
c0100538:	8b 45 08             	mov    0x8(%ebp),%eax
c010053b:	ff d0                	call   *%eax
c010053d:	89 45 f4             	mov    %eax,-0xc(%ebp)
c0100540:	83 7d f4 ff          	cmpl   $0xffffffff,-0xc(%ebp)
c0100544:	75 bd                	jne    c0100503 <cons_intr+0x8>
c0100546:	c9                   	leave  
c0100547:	c3                   	ret    

c0100548 <cons_getc>:
c0100548:	55                   	push   %ebp
c0100549:	89 e5                	mov    %esp,%ebp
c010054b:	83 ec 18             	sub    $0x18,%esp
c010054e:	e8 8f ff ff ff       	call   c01004e2 <kbd_intr>
c0100553:	8b 15 c0 57 10 c0    	mov    0xc01057c0,%edx
c0100559:	a1 c4 57 10 c0       	mov    0xc01057c4,%eax
c010055e:	39 c2                	cmp    %eax,%edx
c0100560:	74 35                	je     c0100597 <cons_getc+0x4f>
c0100562:	a1 c0 57 10 c0       	mov    0xc01057c0,%eax
c0100567:	0f b6 90 c0 55 10 c0 	movzbl -0x3fefaa40(%eax),%edx
c010056e:	0f b6 d2             	movzbl %dl,%edx
c0100571:	89 55 f4             	mov    %edx,-0xc(%ebp)
c0100574:	83 c0 01             	add    $0x1,%eax
c0100577:	a3 c0 57 10 c0       	mov    %eax,0xc01057c0
c010057c:	a1 c0 57 10 c0       	mov    0xc01057c0,%eax
c0100581:	3d 00 02 00 00       	cmp    $0x200,%eax
c0100586:	75 0a                	jne    c0100592 <cons_getc+0x4a>
c0100588:	c7 05 c0 57 10 c0 00 	movl   $0x0,0xc01057c0
c010058f:	00 00 00 
c0100592:	8b 45 f4             	mov    -0xc(%ebp),%eax
c0100595:	eb 05                	jmp    c010059c <cons_getc+0x54>
c0100597:	b8 00 00 00 00       	mov    $0x0,%eax
c010059c:	c9                   	leave  
c010059d:	c3                   	ret    

c010059e <cons_putc>:
c010059e:	55                   	push   %ebp
c010059f:	89 e5                	mov    %esp,%ebp
c01005a1:	83 ec 18             	sub    $0x18,%esp
c01005a4:	8b 45 08             	mov    0x8(%ebp),%eax
c01005a7:	0f b7 c0             	movzwl %ax,%eax
c01005aa:	89 04 24             	mov    %eax,(%esp)
c01005ad:	e8 f3 fb ff ff       	call   c01001a5 <cga_putc>
c01005b2:	c9                   	leave  
c01005b3:	c3                   	ret    

c01005b4 <cputchar>:
c01005b4:	55                   	push   %ebp
c01005b5:	89 e5                	mov    %esp,%ebp
c01005b7:	83 ec 18             	sub    $0x18,%esp
c01005ba:	8b 45 08             	mov    0x8(%ebp),%eax
c01005bd:	89 04 24             	mov    %eax,(%esp)
c01005c0:	e8 d9 ff ff ff       	call   c010059e <cons_putc>
c01005c5:	c9                   	leave  
c01005c6:	c3                   	ret    

c01005c7 <getchar>:
c01005c7:	55                   	push   %ebp
c01005c8:	89 e5                	mov    %esp,%ebp
c01005ca:	83 ec 18             	sub    $0x18,%esp
c01005cd:	e8 76 ff ff ff       	call   c0100548 <cons_getc>
c01005d2:	89 45 f4             	mov    %eax,-0xc(%ebp)
c01005d5:	83 7d f4 00          	cmpl   $0x0,-0xc(%ebp)
c01005d9:	74 f2                	je     c01005cd <getchar+0x6>
c01005db:	8b 45 f4             	mov    -0xc(%ebp),%eax
c01005de:	c9                   	leave  
c01005df:	c3                   	ret    

c01005e0 <iscons>:
c01005e0:	55                   	push   %ebp
c01005e1:	89 e5                	mov    %esp,%ebp
c01005e3:	b8 01 00 00 00       	mov    $0x1,%eax
c01005e8:	5d                   	pop    %ebp
c01005e9:	c3                   	ret    
	...

c01005ec <print_errmsg>:
c01005ec:	55                   	push   %ebp
c01005ed:	89 e5                	mov    %esp,%ebp
c01005ef:	83 ec 18             	sub    $0x18,%esp
c01005f2:	8b 45 08             	mov    0x8(%ebp),%eax
c01005f5:	25 ff 0f 00 00       	and    $0xfff,%eax
c01005fa:	8b 04 85 40 55 10 c0 	mov    -0x3fefaac0(,%eax,4),%eax
c0100601:	89 44 24 08          	mov    %eax,0x8(%esp)
c0100605:	8b 45 08             	mov    0x8(%ebp),%eax
c0100608:	89 44 24 04          	mov    %eax,0x4(%esp)
c010060c:	c7 04 24 45 10 10 c0 	movl   $0xc0101045,(%esp)
c0100613:	e8 14 00 00 00       	call   c010062c <kprintf>
c0100618:	c9                   	leave  
c0100619:	c3                   	ret    
c010061a:	90                   	nop
c010061b:	90                   	nop

c010061c <env_init>:
c010061c:	55                   	push   %ebp
c010061d:	89 e5                	mov    %esp,%ebp
c010061f:	83 ec 10             	sub    $0x10,%esp
c0100622:	c7 45 fc 02 00 00 00 	movl   $0x2,-0x4(%ebp)
c0100629:	c9                   	leave  
c010062a:	c3                   	ret    
c010062b:	90                   	nop

c010062c <kprintf>:
c010062c:	55                   	push   %ebp
c010062d:	89 e5                	mov    %esp,%ebp
c010062f:	5d                   	pop    %ebp
c0100630:	c3                   	ret    
c0100631:	90                   	nop
c0100632:	90                   	nop
c0100633:	90                   	nop

c0100634 <kernel_init>:
c0100634:	55                   	push   %ebp
c0100635:	89 e5                	mov    %esp,%ebp
c0100637:	83 ec 08             	sub    $0x8,%esp
c010063a:	e8 dd ff ff ff       	call   c010061c <env_init>
c010063f:	c9                   	leave  
c0100640:	c3                   	ret    
c0100641:	90                   	nop
c0100642:	90                   	nop
c0100643:	90                   	nop

c0100644 <kmalloc>:
c0100644:	55                   	push   %ebp
c0100645:	89 e5                	mov    %esp,%ebp
c0100647:	b8 00 00 00 00       	mov    $0x0,%eax
c010064c:	5d                   	pop    %ebp
c010064d:	c3                   	ret    
c010064e:	90                   	nop
c010064f:	90                   	nop

c0100650 <memchr>:
c0100650:	55                   	push   %ebp
c0100651:	89 e5                	mov    %esp,%ebp
c0100653:	53                   	push   %ebx
c0100654:	83 ec 20             	sub    $0x20,%esp
c0100657:	8b 45 0c             	mov    0xc(%ebp),%eax
c010065a:	89 c3                	mov    %eax,%ebx
c010065c:	8b 45 08             	mov    0x8(%ebp),%eax
c010065f:	89 45 f8             	mov    %eax,-0x8(%ebp)
c0100662:	eb 20                	jmp    c0100684 <memchr+0x34>
c0100664:	8b 45 f8             	mov    -0x8(%ebp),%eax
c0100667:	0f b6 00             	movzbl (%eax),%eax
c010066a:	0f b6 d0             	movzbl %al,%edx
c010066d:	0f be c3             	movsbl %bl,%eax
c0100670:	39 c2                	cmp    %eax,%edx
c0100672:	75 08                	jne    c010067c <memchr+0x2c>
c0100674:	8b 45 f8             	mov    -0x8(%ebp),%eax
c0100677:	e9 a3 00 00 00       	jmp    c010071f <memchr+0xcf>
c010067c:	83 6d 10 01          	subl   $0x1,0x10(%ebp)
c0100680:	83 45 f8 01          	addl   $0x1,-0x8(%ebp)
c0100684:	83 7d 10 00          	cmpl   $0x0,0x10(%ebp)
c0100688:	74 0a                	je     c0100694 <memchr+0x44>
c010068a:	8b 45 f8             	mov    -0x8(%ebp),%eax
c010068d:	83 e0 03             	and    $0x3,%eax
c0100690:	85 c0                	test   %eax,%eax
c0100692:	75 d0                	jne    c0100664 <memchr+0x14>
c0100694:	8b 45 f8             	mov    -0x8(%ebp),%eax
c0100697:	89 45 f4             	mov    %eax,-0xc(%ebp)
c010069a:	c7 45 f0 01 01 01 01 	movl   $0x1010101,-0x10(%ebp)
c01006a1:	0f be c3             	movsbl %bl,%eax
c01006a4:	0f be d3             	movsbl %bl,%edx
c01006a7:	c1 e2 08             	shl    $0x8,%edx
c01006aa:	09 d0                	or     %edx,%eax
c01006ac:	89 45 ec             	mov    %eax,-0x14(%ebp)
c01006af:	8b 45 ec             	mov    -0x14(%ebp),%eax
c01006b2:	c1 e0 10             	shl    $0x10,%eax
c01006b5:	09 45 ec             	or     %eax,-0x14(%ebp)
c01006b8:	eb 2c                	jmp    c01006e6 <memchr+0x96>
c01006ba:	8b 45 f4             	mov    -0xc(%ebp),%eax
c01006bd:	8b 00                	mov    (%eax),%eax
c01006bf:	33 45 ec             	xor    -0x14(%ebp),%eax
c01006c2:	89 45 e4             	mov    %eax,-0x1c(%ebp)
c01006c5:	8b 45 f0             	mov    -0x10(%ebp),%eax
c01006c8:	8b 55 e4             	mov    -0x1c(%ebp),%edx
c01006cb:	29 c2                	sub    %eax,%edx
c01006cd:	8b 45 f0             	mov    -0x10(%ebp),%eax
c01006d0:	c1 e0 07             	shl    $0x7,%eax
c01006d3:	21 d0                	and    %edx,%eax
c01006d5:	89 45 e0             	mov    %eax,-0x20(%ebp)
c01006d8:	83 7d e0 00          	cmpl   $0x0,-0x20(%ebp)
c01006dc:	75 10                	jne    c01006ee <memchr+0x9e>
c01006de:	83 45 f4 04          	addl   $0x4,-0xc(%ebp)
c01006e2:	83 6d 10 04          	subl   $0x4,0x10(%ebp)
c01006e6:	83 7d 10 03          	cmpl   $0x3,0x10(%ebp)
c01006ea:	77 ce                	ja     c01006ba <memchr+0x6a>
c01006ec:	eb 01                	jmp    c01006ef <memchr+0x9f>
c01006ee:	90                   	nop
c01006ef:	8b 45 f4             	mov    -0xc(%ebp),%eax
c01006f2:	89 45 f8             	mov    %eax,-0x8(%ebp)
c01006f5:	eb 1d                	jmp    c0100714 <memchr+0xc4>
c01006f7:	8b 45 f8             	mov    -0x8(%ebp),%eax
c01006fa:	0f b6 00             	movzbl (%eax),%eax
c01006fd:	0f b6 d0             	movzbl %al,%edx
c0100700:	0f be c3             	movsbl %bl,%eax
c0100703:	39 c2                	cmp    %eax,%edx
c0100705:	75 05                	jne    c010070c <memchr+0xbc>
c0100707:	8b 45 f8             	mov    -0x8(%ebp),%eax
c010070a:	eb 13                	jmp    c010071f <memchr+0xcf>
c010070c:	83 6d 10 01          	subl   $0x1,0x10(%ebp)
c0100710:	83 45 f8 01          	addl   $0x1,-0x8(%ebp)
c0100714:	83 7d 10 00          	cmpl   $0x0,0x10(%ebp)
c0100718:	75 dd                	jne    c01006f7 <memchr+0xa7>
c010071a:	b8 00 00 00 00       	mov    $0x0,%eax
c010071f:	83 c4 20             	add    $0x20,%esp
c0100722:	5b                   	pop    %ebx
c0100723:	5d                   	pop    %ebp
c0100724:	c3                   	ret    
c0100725:	90                   	nop
c0100726:	90                   	nop
c0100727:	90                   	nop

c0100728 <memmove>:
c0100728:	55                   	push   %ebp
c0100729:	89 e5                	mov    %esp,%ebp
c010072b:	83 ec 10             	sub    $0x10,%esp
c010072e:	8b 45 08             	mov    0x8(%ebp),%eax
c0100731:	89 45 fc             	mov    %eax,-0x4(%ebp)
c0100734:	8b 45 0c             	mov    0xc(%ebp),%eax
c0100737:	89 45 f8             	mov    %eax,-0x8(%ebp)
c010073a:	8b 45 f8             	mov    -0x8(%ebp),%eax
c010073d:	3b 45 fc             	cmp    -0x4(%ebp),%eax
c0100740:	73 2d                	jae    c010076f <memmove+0x47>
c0100742:	8b 45 10             	mov    0x10(%ebp),%eax
c0100745:	01 45 f8             	add    %eax,-0x8(%ebp)
c0100748:	8b 45 10             	mov    0x10(%ebp),%eax
c010074b:	01 45 fc             	add    %eax,-0x4(%ebp)
c010074e:	eb 17                	jmp    c0100767 <memmove+0x3f>
c0100750:	83 6d fc 01          	subl   $0x1,-0x4(%ebp)
c0100754:	83 6d f8 01          	subl   $0x1,-0x8(%ebp)
c0100758:	8b 45 f8             	mov    -0x8(%ebp),%eax
c010075b:	0f b6 10             	movzbl (%eax),%edx
c010075e:	8b 45 fc             	mov    -0x4(%ebp),%eax
c0100761:	88 10                	mov    %dl,(%eax)
c0100763:	83 6d 10 01          	subl   $0x1,0x10(%ebp)
c0100767:	83 7d 10 00          	cmpl   $0x0,0x10(%ebp)
c010076b:	75 e3                	jne    c0100750 <memmove+0x28>
c010076d:	eb 27                	jmp    c0100796 <memmove+0x6e>
c010076f:	8b 45 f8             	mov    -0x8(%ebp),%eax
c0100772:	3b 45 fc             	cmp    -0x4(%ebp),%eax
c0100775:	74 1f                	je     c0100796 <memmove+0x6e>
c0100777:	eb 13                	jmp    c010078c <memmove+0x64>
c0100779:	8b 45 f8             	mov    -0x8(%ebp),%eax
c010077c:	0f b6 10             	movzbl (%eax),%edx
c010077f:	8b 45 fc             	mov    -0x4(%ebp),%eax
c0100782:	88 10                	mov    %dl,(%eax)
c0100784:	83 45 fc 01          	addl   $0x1,-0x4(%ebp)
c0100788:	83 45 f8 01          	addl   $0x1,-0x8(%ebp)
c010078c:	83 6d 10 01          	subl   $0x1,0x10(%ebp)
c0100790:	83 7d 10 00          	cmpl   $0x0,0x10(%ebp)
c0100794:	75 e3                	jne    c0100779 <memmove+0x51>
c0100796:	8b 45 fc             	mov    -0x4(%ebp),%eax
c0100799:	c9                   	leave  
c010079a:	c3                   	ret    
c010079b:	90                   	nop

c010079c <strnlen>:
c010079c:	55                   	push   %ebp
c010079d:	89 e5                	mov    %esp,%ebp
c010079f:	83 ec 28             	sub    $0x28,%esp
c01007a2:	8b 45 0c             	mov    0xc(%ebp),%eax
c01007a5:	89 44 24 08          	mov    %eax,0x8(%esp)
c01007a9:	c7 44 24 04 00 00 00 	movl   $0x0,0x4(%esp)
c01007b0:	00 
c01007b1:	8b 45 08             	mov    0x8(%ebp),%eax
c01007b4:	89 04 24             	mov    %eax,(%esp)
c01007b7:	e8 94 fe ff ff       	call   c0100650 <memchr>
c01007bc:	89 45 f4             	mov    %eax,-0xc(%ebp)
c01007bf:	83 7d f4 00          	cmpl   $0x0,-0xc(%ebp)
c01007c3:	74 0e                	je     c01007d3 <strnlen+0x37>
c01007c5:	8b 55 f4             	mov    -0xc(%ebp),%edx
c01007c8:	8b 45 08             	mov    0x8(%ebp),%eax
c01007cb:	89 d1                	mov    %edx,%ecx
c01007cd:	29 c1                	sub    %eax,%ecx
c01007cf:	89 c8                	mov    %ecx,%eax
c01007d1:	eb 03                	jmp    c01007d6 <strnlen+0x3a>
c01007d3:	8b 45 0c             	mov    0xc(%ebp),%eax
c01007d6:	c9                   	leave  
c01007d7:	c3                   	ret    

c01007d8 <memcpy>:
c01007d8:	55                   	push   %ebp
c01007d9:	89 e5                	mov    %esp,%ebp
c01007db:	83 ec 10             	sub    $0x10,%esp
c01007de:	8b 45 08             	mov    0x8(%ebp),%eax
c01007e1:	89 45 fc             	mov    %eax,-0x4(%ebp)
c01007e4:	8b 45 0c             	mov    0xc(%ebp),%eax
c01007e7:	89 45 f8             	mov    %eax,-0x8(%ebp)
c01007ea:	eb 13                	jmp    c01007ff <memcpy+0x27>
c01007ec:	8b 45 f8             	mov    -0x8(%ebp),%eax
c01007ef:	0f b6 10             	movzbl (%eax),%edx
c01007f2:	8b 45 fc             	mov    -0x4(%ebp),%eax
c01007f5:	88 10                	mov    %dl,(%eax)
c01007f7:	83 45 fc 01          	addl   $0x1,-0x4(%ebp)
c01007fb:	83 45 f8 01          	addl   $0x1,-0x8(%ebp)
c01007ff:	83 7d 10 00          	cmpl   $0x0,0x10(%ebp)
c0100803:	0f 95 c0             	setne  %al
c0100806:	83 6d 10 01          	subl   $0x1,0x10(%ebp)
c010080a:	84 c0                	test   %al,%al
c010080c:	75 de                	jne    c01007ec <memcpy+0x14>
c010080e:	8b 45 08             	mov    0x8(%ebp),%eax
c0100811:	c9                   	leave  
c0100812:	c3                   	ret    
c0100813:	90                   	nop

c0100814 <strncmp>:
c0100814:	55                   	push   %ebp
c0100815:	89 e5                	mov    %esp,%ebp
c0100817:	83 ec 28             	sub    $0x28,%esp
c010081a:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%ebp)
c0100821:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%ebp)
c0100828:	c7 45 ec 00 00 00 00 	movl   $0x0,-0x14(%ebp)
c010082f:	c7 45 e8 00 00 00 00 	movl   $0x0,-0x18(%ebp)
c0100836:	8b 45 10             	mov    0x10(%ebp),%eax
c0100839:	3d 00 01 00 00       	cmp    $0x100,%eax
c010083e:	76 05                	jbe    c0100845 <strncmp+0x31>
c0100840:	b8 00 01 00 00       	mov    $0x100,%eax
c0100845:	89 45 ec             	mov    %eax,-0x14(%ebp)
c0100848:	8b 45 ec             	mov    -0x14(%ebp),%eax
c010084b:	89 44 24 04          	mov    %eax,0x4(%esp)
c010084f:	8b 45 08             	mov    0x8(%ebp),%eax
c0100852:	89 04 24             	mov    %eax,(%esp)
c0100855:	e8 42 ff ff ff       	call   c010079c <strnlen>
c010085a:	89 45 f4             	mov    %eax,-0xc(%ebp)
c010085d:	8b 45 ec             	mov    -0x14(%ebp),%eax
c0100860:	89 44 24 04          	mov    %eax,0x4(%esp)
c0100864:	8b 45 0c             	mov    0xc(%ebp),%eax
c0100867:	89 04 24             	mov    %eax,(%esp)
c010086a:	e8 2d ff ff ff       	call   c010079c <strnlen>
c010086f:	89 45 f0             	mov    %eax,-0x10(%ebp)
c0100872:	8b 55 f4             	mov    -0xc(%ebp),%edx
c0100875:	8b 45 f0             	mov    -0x10(%ebp),%eax
c0100878:	39 d0                	cmp    %edx,%eax
c010087a:	73 02                	jae    c010087e <strncmp+0x6a>
c010087c:	89 d0                	mov    %edx,%eax
c010087e:	89 45 e8             	mov    %eax,-0x18(%ebp)
c0100881:	83 7d e8 00          	cmpl   $0x0,-0x18(%ebp)
c0100885:	0f 95 c0             	setne  %al
c0100888:	83 6d e8 01          	subl   $0x1,-0x18(%ebp)
c010088c:	84 c0                	test   %al,%al
c010088e:	74 1d                	je     c01008ad <strncmp+0x99>
c0100890:	8b 45 08             	mov    0x8(%ebp),%eax
c0100893:	0f b6 10             	movzbl (%eax),%edx
c0100896:	8b 45 0c             	mov    0xc(%ebp),%eax
c0100899:	0f b6 00             	movzbl (%eax),%eax
c010089c:	38 c2                	cmp    %al,%dl
c010089e:	0f 94 c0             	sete   %al
c01008a1:	83 45 08 01          	addl   $0x1,0x8(%ebp)
c01008a5:	83 45 0c 01          	addl   $0x1,0xc(%ebp)
c01008a9:	84 c0                	test   %al,%al
c01008ab:	75 d4                	jne    c0100881 <strncmp+0x6d>
c01008ad:	83 7d e8 00          	cmpl   $0x0,-0x18(%ebp)
c01008b1:	75 07                	jne    c01008ba <strncmp+0xa6>
c01008b3:	b8 00 00 00 00       	mov    $0x0,%eax
c01008b8:	eb 28                	jmp    c01008e2 <strncmp+0xce>
c01008ba:	8b 45 08             	mov    0x8(%ebp),%eax
c01008bd:	0f b6 00             	movzbl (%eax),%eax
c01008c0:	0f b6 d0             	movzbl %al,%edx
c01008c3:	8b 45 0c             	mov    0xc(%ebp),%eax
c01008c6:	0f b6 00             	movzbl (%eax),%eax
c01008c9:	0f b6 c0             	movzbl %al,%eax
c01008cc:	89 d1                	mov    %edx,%ecx
c01008ce:	29 c1                	sub    %eax,%ecx
c01008d0:	89 c8                	mov    %ecx,%eax
c01008d2:	85 c0                	test   %eax,%eax
c01008d4:	7e 07                	jle    c01008dd <strncmp+0xc9>
c01008d6:	b8 01 00 00 00       	mov    $0x1,%eax
c01008db:	eb 05                	jmp    c01008e2 <strncmp+0xce>
c01008dd:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
c01008e2:	c9                   	leave  
c01008e3:	c3                   	ret    

c01008e4 <strndup>:
c01008e4:	55                   	push   %ebp
c01008e5:	89 e5                	mov    %esp,%ebp
c01008e7:	83 ec 28             	sub    $0x28,%esp
c01008ea:	8b 45 0c             	mov    0xc(%ebp),%eax
c01008ed:	89 44 24 04          	mov    %eax,0x4(%esp)
c01008f1:	8b 45 08             	mov    0x8(%ebp),%eax
c01008f4:	89 04 24             	mov    %eax,(%esp)
c01008f7:	e8 a0 fe ff ff       	call   c010079c <strnlen>
c01008fc:	89 45 f4             	mov    %eax,-0xc(%ebp)
c01008ff:	8b 45 f4             	mov    -0xc(%ebp),%eax
c0100902:	83 c0 01             	add    $0x1,%eax
c0100905:	89 04 24             	mov    %eax,(%esp)
c0100908:	e8 37 fd ff ff       	call   c0100644 <kmalloc>
c010090d:	89 45 f0             	mov    %eax,-0x10(%ebp)
c0100910:	83 7d f0 00          	cmpl   $0x0,-0x10(%ebp)
c0100914:	75 07                	jne    c010091d <strndup+0x39>
c0100916:	b8 00 00 00 00       	mov    $0x0,%eax
c010091b:	eb 25                	jmp    c0100942 <strndup+0x5e>
c010091d:	8b 45 f4             	mov    -0xc(%ebp),%eax
c0100920:	8b 55 f0             	mov    -0x10(%ebp),%edx
c0100923:	8d 04 02             	lea    (%edx,%eax,1),%eax
c0100926:	c6 00 00             	movb   $0x0,(%eax)
c0100929:	8b 45 f4             	mov    -0xc(%ebp),%eax
c010092c:	89 44 24 08          	mov    %eax,0x8(%esp)
c0100930:	8b 45 08             	mov    0x8(%ebp),%eax
c0100933:	89 44 24 04          	mov    %eax,0x4(%esp)
c0100937:	8b 45 f0             	mov    -0x10(%ebp),%eax
c010093a:	89 04 24             	mov    %eax,(%esp)
c010093d:	e8 96 fe ff ff       	call   c01007d8 <memcpy>
c0100942:	c9                   	leave  
c0100943:	c3                   	ret    

c0100944 <strncpy>:
c0100944:	55                   	push   %ebp
c0100945:	89 e5                	mov    %esp,%ebp
c0100947:	83 ec 10             	sub    $0x10,%esp
c010094a:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%ebp)
c0100951:	8b 45 08             	mov    0x8(%ebp),%eax
c0100954:	89 45 f8             	mov    %eax,-0x8(%ebp)
c0100957:	eb 1d                	jmp    c0100976 <strncpy+0x32>
c0100959:	8b 45 0c             	mov    0xc(%ebp),%eax
c010095c:	0f b6 10             	movzbl (%eax),%edx
c010095f:	8b 45 08             	mov    0x8(%ebp),%eax
c0100962:	88 10                	mov    %dl,(%eax)
c0100964:	83 45 08 01          	addl   $0x1,0x8(%ebp)
c0100968:	8b 45 0c             	mov    0xc(%ebp),%eax
c010096b:	0f b6 00             	movzbl (%eax),%eax
c010096e:	84 c0                	test   %al,%al
c0100970:	74 04                	je     c0100976 <strncpy+0x32>
c0100972:	83 45 0c 01          	addl   $0x1,0xc(%ebp)
c0100976:	8b 45 fc             	mov    -0x4(%ebp),%eax
c0100979:	3b 45 10             	cmp    0x10(%ebp),%eax
c010097c:	0f 92 c0             	setb   %al
c010097f:	83 45 fc 01          	addl   $0x1,-0x4(%ebp)
c0100983:	84 c0                	test   %al,%al
c0100985:	75 d2                	jne    c0100959 <strncpy+0x15>
c0100987:	8b 45 f8             	mov    -0x8(%ebp),%eax
c010098a:	c9                   	leave  
c010098b:	c3                   	ret    

c010098c <strncat>:
c010098c:	55                   	push   %ebp
c010098d:	89 e5                	mov    %esp,%ebp
c010098f:	83 ec 28             	sub    $0x28,%esp
c0100992:	8b 45 10             	mov    0x10(%ebp),%eax
c0100995:	89 44 24 04          	mov    %eax,0x4(%esp)
c0100999:	8b 45 08             	mov    0x8(%ebp),%eax
c010099c:	89 04 24             	mov    %eax,(%esp)
c010099f:	e8 f8 fd ff ff       	call   c010079c <strnlen>
c01009a4:	03 45 08             	add    0x8(%ebp),%eax
c01009a7:	89 45 f4             	mov    %eax,-0xc(%ebp)
c01009aa:	eb 13                	jmp    c01009bf <strncat+0x33>
c01009ac:	8b 45 0c             	mov    0xc(%ebp),%eax
c01009af:	0f b6 10             	movzbl (%eax),%edx
c01009b2:	8b 45 f4             	mov    -0xc(%ebp),%eax
c01009b5:	88 10                	mov    %dl,(%eax)
c01009b7:	83 45 f4 01          	addl   $0x1,-0xc(%ebp)
c01009bb:	83 45 0c 01          	addl   $0x1,0xc(%ebp)
c01009bf:	83 7d 10 00          	cmpl   $0x0,0x10(%ebp)
c01009c3:	0f 95 c0             	setne  %al
c01009c6:	83 6d 10 01          	subl   $0x1,0x10(%ebp)
c01009ca:	84 c0                	test   %al,%al
c01009cc:	74 0a                	je     c01009d8 <strncat+0x4c>
c01009ce:	8b 45 f4             	mov    -0xc(%ebp),%eax
c01009d1:	0f b6 00             	movzbl (%eax),%eax
c01009d4:	84 c0                	test   %al,%al
c01009d6:	75 d4                	jne    c01009ac <strncat+0x20>
c01009d8:	83 7d 10 00          	cmpl   $0x0,0x10(%ebp)
c01009dc:	75 06                	jne    c01009e4 <strncat+0x58>
c01009de:	8b 45 f4             	mov    -0xc(%ebp),%eax
c01009e1:	c6 00 00             	movb   $0x0,(%eax)
c01009e4:	8b 45 08             	mov    0x8(%ebp),%eax
c01009e7:	c9                   	leave  
c01009e8:	c3                   	ret    
c01009e9:	90                   	nop
c01009ea:	90                   	nop
c01009eb:	90                   	nop

c01009ec <memset>:
c01009ec:	55                   	push   %ebp
c01009ed:	89 e5                	mov    %esp,%ebp
c01009ef:	53                   	push   %ebx
c01009f0:	8b 5d 08             	mov    0x8(%ebp),%ebx
c01009f3:	eb 08                	jmp    c01009fd <memset+0x11>
c01009f5:	8b 45 0c             	mov    0xc(%ebp),%eax
c01009f8:	88 03                	mov    %al,(%ebx)
c01009fa:	83 c3 01             	add    $0x1,%ebx
c01009fd:	83 7d 10 00          	cmpl   $0x0,0x10(%ebp)
c0100a01:	0f 95 c0             	setne  %al
c0100a04:	83 6d 10 01          	subl   $0x1,0x10(%ebp)
c0100a08:	84 c0                	test   %al,%al
c0100a0a:	75 e9                	jne    c01009f5 <memset+0x9>
c0100a0c:	8b 45 08             	mov    0x8(%ebp),%eax
c0100a0f:	5b                   	pop    %ebx
c0100a10:	5d                   	pop    %ebp
c0100a11:	c3                   	ret    
c0100a12:	90                   	nop
c0100a13:	90                   	nop

c0100a14 <strchr>:
c0100a14:	55                   	push   %ebp
c0100a15:	89 e5                	mov    %esp,%ebp
c0100a17:	83 ec 28             	sub    $0x28,%esp
c0100a1a:	8b 45 08             	mov    0x8(%ebp),%eax
c0100a1d:	c7 44 24 04 00 01 00 	movl   $0x100,0x4(%esp)
c0100a24:	00 
c0100a25:	89 04 24             	mov    %eax,(%esp)
c0100a28:	e8 6f fd ff ff       	call   c010079c <strnlen>
c0100a2d:	89 45 f4             	mov    %eax,-0xc(%ebp)
c0100a30:	83 7d f4 00          	cmpl   $0x0,-0xc(%ebp)
c0100a34:	75 05                	jne    c0100a3b <strchr+0x27>
c0100a36:	8b 45 08             	mov    0x8(%ebp),%eax
c0100a39:	eb 19                	jmp    c0100a54 <strchr+0x40>
c0100a3b:	8b 45 f4             	mov    -0xc(%ebp),%eax
c0100a3e:	89 44 24 08          	mov    %eax,0x8(%esp)
c0100a42:	8b 45 0c             	mov    0xc(%ebp),%eax
c0100a45:	89 44 24 04          	mov    %eax,0x4(%esp)
c0100a49:	8b 45 08             	mov    0x8(%ebp),%eax
c0100a4c:	89 04 24             	mov    %eax,(%esp)
c0100a4f:	e8 fc fb ff ff       	call   c0100650 <memchr>
c0100a54:	c9                   	leave  
c0100a55:	c3                   	ret    
	...

c0100a58 <pcall_backtrace>:
c0100a58:	55                   	push   %ebp
c0100a59:	89 e5                	mov    %esp,%ebp
c0100a5b:	b8 00 00 00 00       	mov    $0x0,%eax
c0100a60:	5d                   	pop    %ebp
c0100a61:	c3                   	ret    
c0100a62:	90                   	nop
c0100a63:	90                   	nop

c0100a64 <msg_print>:
c0100a64:	55                   	push   %ebp
c0100a65:	89 e5                	mov    %esp,%ebp
c0100a67:	83 ec 18             	sub    $0x18,%esp
c0100a6a:	8b 45 08             	mov    0x8(%ebp),%eax
c0100a6d:	89 44 24 04          	mov    %eax,0x4(%esp)
c0100a71:	c7 04 24 ff ff ff 00 	movl   $0xffffff,(%esp)
c0100a78:	e8 02 00 00 00       	call   c0100a7f <write_string>
c0100a7d:	c9                   	leave  
c0100a7e:	c3                   	ret    

c0100a7f <write_string>:
c0100a7f:	55                   	push   %ebp
c0100a80:	89 e5                	mov    %esp,%ebp
c0100a82:	83 ec 10             	sub    $0x10,%esp
c0100a85:	c7 45 fc 00 80 0b 00 	movl   $0xb8000,-0x4(%ebp)
c0100a8c:	eb 21                	jmp    c0100aaf <write_string+0x30>
c0100a8e:	8b 45 0c             	mov    0xc(%ebp),%eax
c0100a91:	0f b6 10             	movzbl (%eax),%edx
c0100a94:	8b 45 fc             	mov    -0x4(%ebp),%eax
c0100a97:	88 10                	mov    %dl,(%eax)
c0100a99:	83 45 0c 01          	addl   $0x1,0xc(%ebp)
c0100a9d:	83 45 fc 01          	addl   $0x1,-0x4(%ebp)
c0100aa1:	8b 45 08             	mov    0x8(%ebp),%eax
c0100aa4:	89 c2                	mov    %eax,%edx
c0100aa6:	8b 45 fc             	mov    -0x4(%ebp),%eax
c0100aa9:	88 10                	mov    %dl,(%eax)
c0100aab:	83 45 fc 01          	addl   $0x1,-0x4(%ebp)
c0100aaf:	8b 45 0c             	mov    0xc(%ebp),%eax
c0100ab2:	0f b6 00             	movzbl (%eax),%eax
c0100ab5:	84 c0                	test   %al,%al
c0100ab7:	75 d5                	jne    c0100a8e <write_string+0xf>
c0100ab9:	c9                   	leave  
c0100aba:	c3                   	ret    
c0100abb:	90                   	nop

c0100abc <kern_debug>:
c0100abc:	55                   	push   %ebp
c0100abd:	89 e5                	mov    %esp,%ebp
c0100abf:	83 ec 18             	sub    $0x18,%esp
c0100ac2:	c7 04 24 53 10 10 c0 	movl   $0xc0101053,(%esp)
c0100ac9:	e8 96 ff ff ff       	call   c0100a64 <msg_print>
c0100ace:	eb fe                	jmp    c0100ace <kern_debug+0x12>
