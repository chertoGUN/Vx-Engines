;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;
;																										 ;
;																										 ;
;                                                            											 ;
;																										 ;
;                                       																 ;
;                                     xxxxxxxxxxxxxxxxxxxxxxxxxx      xxxxxxxxxxxxxxxxxxx				 ;
;                                     xxxxxxxxxxxxxxxxxxxxxxxxxx     xxxxxxxxxxxxxxxxxxxx     			 ;
;                                     xxxxxxxxxxxxxxxxxxxxxxxxxx    xxxxxxxxxxxxxxxxxxxxx      			 ;
;        x                         x  xxxxxxxxxxxxxxxxxxxxxxxxxx   xxxxxxxxxxxxxxxxxxxxxx				 ;
;        xxx                     xxx           xxxxxxxx           xxxxxxx		  xxxxxxx      			 ; 
;        xxxxx                 xxxxx           xxxxxxxx           xxxxxxx								 ;
;        xxxxxxx             xxxxxxx           xxxxxxxx           xxxxxxx								 ;
;        xxxxxxxxx         xxxxxxxxx           xxxxxxxx           xxxxxxx								 ;
;         xxxxxxxxxx     xxxxxxxxxx            xxxxxxxx           xxxxxxx								 ;
;           xxxxxxxxxx xxxxxxxxxx              xxxxxxxx           xxxxxxx								 ;
;             xxxxxxxxxxxxxxxxx                xxxxxxxx           xxxxxxx								 ;
;               xxxxxxxxxxxxx                  xxxxxxxx           xxxxxxx       xxxxxxxxx				 ;
;                xxxxxxxxxxx                   xxxxxxxx           xxxxxxx       xxxxxxxxx				 ;
;              xx  xxxxxxx  xx                 xxxxxxxx           xxxxxxx       xxxxxxxxx				 ;
;             xxxx  xxxxx  xxxx                xxxxxxxx           xxxxxxx         xxxxxxx				 ;
;            xxxxxx   x   xxxxxx               xxxxxxxx           xxxxxxx         xxxxxxx				 ;
;           xxxxxxxx     xxxxxxxx              xxxxxxxx            xxxxxxxxxxxxxxxxxxxxxx 				 ;
;          xxxxxxxx       xxxxxxxx             xxxxxxxx             xxxxxxxxxxxxxxxxxxxxx 				 ;
;         xxxxxxxx         xxxxxxxx            xxxxxxxx              xxxxxxxxxxxxxxxxxxxx 				 ;
;        xxxxxxxx           xxxxxxxx           xxxxxxxx               xxxxxxxxxxxxxxxxxxx				 ;
;																										 ;
;																										 ;
;																										 ;
;																										 ;
;																										 ; 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;
;							eXperimental/eXtended/eXecutable Trash Generator							 ;
;												  xTG													 ;
;												xtg.inc													 ;
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;
;																										 ;
;												  xD													 ;
;																										 ;
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;
;���������� 䠩� xtg.inc (��� xtg.asm, logic.asm, faka.asm); 											 ;
;����� ��騥 ���祭��; ���� ���祭�� ᬮ�� � �㭪�, ॠ�����饩 ����室��� �����; 				 ;
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;
;v2.0.0


																		;m1x
																		;pr0mix@mail.ru
																		;EOF



;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
;�᭮��� ���祭��/����⠭�� 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
NUM_INSTR				equ		44 										;������⢮ (���-��) ����㯭�� �������権 � ������ ����; 
MAX_STAT				equ		1001									;
MAX_SIZE_INSTR			equ		1001 									;max ࠧ��� ������樨 ��� �ࠢ����� (����� ������ � ��� 10000h, ����� xD); 
																		;���� ��� ���᫥��� �������쭮�� ࠧ��� ����㯭�� ��� �����樨 ������� (ᬮ�ਢ ���� etc); 
NUM_HASH				equ		78										;���-�� ��襩 (�� ��� ������襪)
WINAPI_MAX_SIZE			equ		(06 + 10 * 10 + 01)						;max ࠧ��� ������-�������樨: �맮� ������ (6 ����) + ��।������ ��ࠬ���� (10 ��� * 10 ���� (ࠧ��� ����� ��㪨)); 

size_of_stack_commit	equ		5000h									;���� ����㠫쭮� �����, �뤥�塞�� ��� �⥪ (����� ������� ���� �⥪� � esp �� ᢮� ���� � �뤥������ �����); 
																		;�� ����室����� ������ ���祭�� 㢥�����; 

;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
;�᭮��� ���祭��/����⠭�� 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 



;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
;�ᯮ����⥫�� ����⠭��; 
;��� ࠡ��� ������; 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
vl_vstack_size			equ		5000h									;ࠧ��� ����㠫쭮�� �����
vl_vstack_small_size	equ		1000h									;ࠧ��� �������⥫쭮�� ����㠫쭮�� �⥪�
vl_regs_states			equ		100										;���-�� ��������� ���ﭨ� ��� ������� ����㠫쭮�� ॣ�
vl_lv_num				equ		32										;���-�� �஢��塞�� �������� ��६����� 
vl_lv_states			equ		50										;���-�� ��������� ���ﭨ� ��� ������� �����-��� =)
vl_instr_buf_size		equ		(MAX_SIZE_INSTR + 1000h)				;ࠧ��� ���� ��� ����᪠ ������� (⠬ �� �㤥� ����஢��� ������� ��㣨� ᯥ�. ��); 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
;�ᯮ����⥫�� ����⠭��; 
;��� ࠡ��� ������; 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx





;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
;�������� ��� ������ xTG;
;+ �� ������;
;XTG_TRASH_GEN				-	�᭮���� �������, �� ���� ��।����� ������ xTG ��� �����樨 ����; ([0] - in_param, [1] - out_param); 
;XTG_EXT_TRASH_GEN			-	�ᯮ����⥫쭠� �������, ���ࠧ㬥������ �࠭���� � ��� ࠧ��筮� ���� 
;XTG_FUNC_STRUCT			-	������ઠ, ����� �㦭� ���/�� �����樨 �㭪権 (� �஫�����, 
;								��������� etc); 
;XTG_DATA_STRUCT			-	�������, ���� ���ன ᮤ�ঠ� ���� � ࠧ���� �����⥩ �����, 
;								�㦭�� ��� �����樨 ����-���� � ����-������;
;FAKA_FAKEAPI_GEN			-	�������, �᭮���� ��� ������ FAKA;
;XTG_LOGIC_STRUCT			-	�������, ���� �� ������ ��।����� (� EAX) ��᫥ ���樠����樨 let_init (LET �孮�����);
;								������� ��᫥ ���樠����樨 ��������� �㦭묨 ���祭�ﬨ;
;								�������a ᮤ�ন� ���� �����, ����室��� ��� ࠡ��� �㭮� �஢�ન/����஥��� ������ ����-���� (let); 
;XTG_INSTR_DATA_STRUCT		-	�������, ����� ���������� ������� xTG, � ���� �⮩ ������ ��।����� 
;								��� �㭪� let_main;
;								��� � ���� ������� ���� ������� ��� �஢�ન ������, ࠧ��� �⮩ ������� � �.�. (ᬮ�� ����+)! 
;XTG_INSTR_PARS_STRUCT		-	�����, ����� ���������� ����஬ ��� ���� � ���������/���४�� ������; 
;								� ����� �⮩ �������� 㪠�뢠��, ����� ��ࠬ���� ᮤ�ন� ࠧ��࠭��� �����, 
;								᪮�쪮 ��, ࠧ���� 䫠�� etc; 
;XTG_REGS_CURV_STRUCT		-	������� ��� ⥪��� ���ﭨ� ����㠫��� ॣ�� � + ��᪨;
;XTG_REGS_STRUCT			-	����� ��� �࠭���� ��� ᮡ࠭��� ���ﭨ� ����㠫��� ॣ�� (��� ���������/���४�� ������); 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
;--------------------------------------------------------------------------------------------------------
XTG_TRASH_GEN				struct
	fmode							dd					?				;[0]; ०�� �����樨 ����: XTG_MASK ��� XTG_REALISTIC 			
	rang_addr 						dd					?				;[0]; ���� ���;
	faka_addr						dd					?				;[0]; ���� ������ �����樨 �������� ������襪; 
	faka_struct_addr				dd					?				;[0]; ���� �������� FAKA_FAKEAPI_GEN ��� ������ �����樨 ����-���; 
	xfunc_struct_addr				dd					?				;[0]; ���� �������� XTG_FUNC_STRUCT - �᫨ ����������� �㭪� �� �⨬ ������� (xTG), � �㦭� ������� �������� ������ � ���⨥� ebp etc, ⮣�� ������塞 ������ �������� � ��।��� �� ���� �; 
	xdata_struct_addr				dd					?				;[0]; ���� �������� XTG_DATA_STRUCT - �᫨ �㦭� �����樨 ������, � ������ ���� mem32 (address), � ⠪�� ����� ������� ����-����� - ������塞 ⠪�� ��������; 
	alloc_addr						dd					?				;[0]; ���� �㭪樨 �뤥����� �����
	free_addr						dd					?				;[0]; ���� �㭪� �᢮�������� �����
	tw_trash_addr					dd					?				;[0]; tw - To Write; ����, �㤠 �����뢠�� ������㥬�� ���쬮
	trash_size						dd					?				;[0]; ࠧ��� �⮣� ���쬠
	xmask1							dd					?				;[0]; 64-��⭠� ��᪠ ��� �����樨 ����
	xmask2							dd					?				;[0]; �ਬ����� � ०��� XTG_MASK; 
	fregs							dd					?				;[0]; ������ ॣ����� (ॣ�); 
	nobw							dd					?				;[1]; number of bytes written; ���-�� ॠ�쭮 ����ᠭ��� ���⮢ (ࠧ��� ॠ�쭮 ᣥ��७���� ���蠪�); 
	ep_trash_addr					dd					?				;[1]; address of entry point; �窠 �室� � ����;
	fnw_addr						dd					?				;[1]; address for next write; ���� ��� ���쭥�襩 ����� ����; 	 
XTG_TRASH_GEN				ends 
;--------------------------------------------------------------------------------------------------------

;--------------------------------------------------------------------------------------------------------
XTG_EXT_TRASH_GEN			struct
	ofs_addr						dd					?				;[0]; opcode frequency statistics
	one_byte_opcode_addr			dd					?				;[0]; ���� ⠡���� �������⮢�� ������; 
	xlogic_struct_addr				dd					?				;[0]; ���� �������� XTG_LOGIC_STRUCT
XTG_EXT_TRASH_GEN			ends
;--------------------------------------------------------------------------------------------------------

;--------------------------------------------------------------------------------------------------------
XTG_FUNC_STRUCT				struct
	func_addr						dd					?				;[0]; adrress of func; ���� �㭪樨 (����, �� ���஬� �㤥� ��� 㦥 ᣥ���஢��� �㭪�);
	func_size						dd					?				;[0]; size of func; ࠧ��� �㭪� (etc); 
	call_num						dd					?				;[0]; numbers of call's in func; ���-�� �맮��� � �㭪� (���-�� call'��); 
	local_num						dd					?				;[0]; numbers of local variable in func; ���-�� �������� ��६����� � ������ �㭪�; 
	param_num						dd					?				;[0]; numbers of input parameters in func; ���-�� �室��� ��ࠬ��஢;
XTG_FUNC_STRUCT				ends 
;--------------------------------------------------------------------------------------------------------

;--------------------------------------------------------------------------------------------------------
XTG_DATA_STRUCT				struct
	xmask							dd					?				;[0]; ��᪠ ��� �����樨 ����-������ 
	rdata_addr						dd					?				;[0]; ���� ������ �����, � ������ ���� ᣥ���஢���� ����-����� 
	rdata_size						dd					?				;[0]; ࠧ��� �⮩ ������ �����
	rdata_pva						dd					?				;[0]; ����� ���� ��।����� � rdata_addr: ��᮫��� 䨧��᪨� � 䠩�� ��� ����㠫�� � �����?;
	;wdata_addr						dd					?				;[0]; 
	;wdata_size						dd					?				;[0]; 
	xdata_addr						dd					?				;[0]; ���� ������ �����, ���� ���ன ���� �砢�⢮���� � �����樨 ����-���� (VA); 
	xdata_size						dd					?				;[0]; ৬�� �⮩ ������ �����;
	;xdata_pva						dd					?				;[0]; 
	nobw							dd					?				;[1]; ���-�� ॠ�쭮 ����ᠭ��� ���⮢ ����-������; 
XTG_DATA_STRUCT				ends
;--------------------------------------------------------------------------------------------------------

;--------------------------------------------------------------------------------------------------------
FAKA_FAKEAPI_GEN			struct
	mapped_addr						dd					?				;[0]; ���� �������� 
	rang_addr						dd					?				;[0]; ���� ���
	alloc_addr						dd					?				;[0]; ���� �㭪樨 �뤥����� �����
	free_addr						dd					?				;[0]; ���� �㭪樨 �᢮�������� �����
	xfunc_struct_addr				dd					?				;[0]; ���� �������� XTG_FUNC_STRUCT - �᫨ ����������� �㭪� �� �⨬ ������� (xTG), � �㦭� ������� �������� ������ � ���⨥� ebp etc, ⮣�� ������塞 ������ �������� � ��।��� �� ���� �; 
	xdata_struct_addr				dd					?				;[0]; ���� �������� XTG_DATA_STRUCT - �᫨ �㦭� �����樨 ������, � ������ ���� mem32 (address), � ⠪�� ����� ������� ����-����� - ������塞 ⠪�� ��������; 
	tw_api_addr						dd					?				;[0]; ����, �㤠 ������� ᣥ���஢���� ������� �맮� ������ �㭪樨;
	api_size						dd					?				;[0]; max ࠧ��� ������-�������樨
	api_hash						dd					?				;[0] [1]; ��� �� ����� ������ (����� ���஡�� ��� ��� ����� ��� ������� � ������ ��㣮� �⠩ � ����� �� �������); 
	api_va							dd					?				;[1]; VirtualAddress (VA); 
	nobw							dd					? 				;[1]; ���-�� ॠ�쭮 ����ᠭ��� ����
	fnw_addr						dd					?				;[1]; ���� ��� ���쭥�襩 ����� ����; 
FAKA_FAKEAPI_GEN			ends

;--------------------------------------------------------------------------------------------------------

;--------------------------------------------------------------------------------------------------------
XTG_LOGIC_STRUCT			struct
	xalloc_buf_addr					dd					?				;[1]; ���� �ᥩ �뤥������ ������ ����� (� ⠪�� ���� ������ ��������); 
	xalloc_buf_size					dd					?				;[1]; ࠧ��� �⮩ �����; 
	flags_addr						dd					?				;[1]; ���� �����, � ���ன ���� �࠭����� 䫠�� ��㫨�㥬��� ���� (pushfd/popfd); 
	xinstr_data_struct_addr			dd					?				;[1]; ���� ������ XTG_INSTR_DATA_STRUCT; ����� �� �������/�������樨, ������ ᫥��� �஠������஢��� (�������� � ��㫨��); 
	xinstr_pars_struct_addr			dd					?				;[1]; ���� ������ XTG_INSTR_PARS_STRUCT, ᮤ�ঠ��� ����� � �ய��ᥭ��� �������; 
	vstack_addr						dd					?				;[1]; ���� �뤥������ ����� ��� ����㠫�� ����
	vstack_small_addr				dd					?				;[1]; ���� �뤥�. ����� ��� �������⥫�� ����. �⥪;
	xregs_curv_struct_addr			dd					?				;[1]; XTG_REGS_STRUCT -> ⥪�騥 ���祭�� ����㠫��� ॣ�� + ��᪨;
	xregs_states_addr				dd					?				;[1]; ��� ���ﭨ� ॣ��; 
	xlv_addr						dd					?				;[1]; ���� ��࠭��� �����-��६ + ��᪨ + �᫮ ��⨢��� �.�.; (�� ⥪�騥 ���祭�� ����� � ����㠫쭮� �⥪�); 
	xlv_states_addr					dd					?				;[1]; ��� ���ﭨ� �����-��஢;
	xdata_addr						dd					?				;[1]; ��� ������ �����; 
	instr_buf_addr					dd					?				;[1]; ����, � ����� �㤥� ����஢����� ��������� ��� �믮������; 
XTG_LOGIC_STRUCT			ends
;--------------------------------------------------------------------------------------------------------

;--------------------------------------------------------------------------------------------------------
XTG_INSTR_DATA_STRUCT		struct
	instr_addr						dd					?				;[0]; ���� �������樨, ������ ���� �஢����
	instr_size						dd					?				;[0]; �� ࠧ���		
	flags							dd					?				;[0]; 䫠�� (inc_dec_r32 etc);
	param_1							dd					?				;[0]; ��� �࠭���� ����� ॣ�, � ⠪�� �������� ��⠭���� ���襣� ��� � 1, �� ����砥�, �� �� ����ਬ ������� ��� �������樨 (� ४��ᨨ); 
	norb							dd					?				;[0]; number of remaining bytes -> ���-�� ��⠢���� ���⮢ ��� ����� ���� (�㦭� ��� ���४⭮� ࠡ��� �஢�ન); 
XTG_INSTR_DATA_STRUCT		ends
;--------------------------------------------------------------------------------------------------------

;--------------------------------------------------------------------------------------------------------
XTG_INSTR_PARS_STRUCT		struct
	flags							dd					?				;[0]; 䫠�� ��� ���������
	param_1							dd					?				;[0]; ����� �࠭���� ���� ����� ॣ���� ���� ���� � ����� (� ����� �� �࠭����� �᫮?)
	param_2							dd					?				;[0]; ����� �࠭���� ���� ����� ॣ�, ���� ���� � �����, ���� �᫮
	param_3							dd					?				;[0]; � ����� ���� ᮮ�-�� ॣ��, �ਭ������ ���⨥ � �⤠� (give) ���祭�� (��ࠬ���� 1); (��� 0 - eax etc); 
XTG_INSTR_PARS_STRUCT		ends
;--------------------------------------------------------------------------------------------------------

;--------------------------------------------------------------------------------------------------------
XTG_REGS_STRUCT				struct
	x_eax							dd					?				;[0]; ���祭�� ����㠫��� ॣ�� (��� ����樨 ����); 
	x_ecx							dd					?				;[0]; �� ����� �।�����祭� ��� ��� �࠭���� ⥪��� ���祭�� ����㠫��� ॣ��, 
	x_edx							dd					?				;[0]; ⠪ � ��� �࠭���� ��� ����祭��� ���ﭨ� �� ॣ�� 
	x_ebx							dd					?				;[0]; ��� �⮣� �뤥������ ࠧ�� ���⪨ ����� ��� �࠭���� ���ᨢ�� �⮩ �������� ��� ࠧ�� �����; 
	x_esp							dd					?				;[0]; 
	x_ebp							dd					?				;[0]; 
	x_esi							dd					?				;[0]; 
	x_edi							dd					?				;[0]; 
XTG_REGS_STRUCT				ends
;--------------------------------------------------------------------------------------------------------

;--------------------------------------------------------------------------------------------------------
XTG_REGS_CURV_STRUCT		struct
	xregs_struct					XTG_REGS_STRUCT		<>				;[0]; ���� �������� XTG_REGS_STRUCT
	regs_init						dd					?				;[0]; �ந��樠����஢���� ॣ� (�� ����୮� ���樠����樨); 
	regs_used						dd					?				;[0]; ॣ�, ����� ����� �� (��� �⤠� ᢮�� ���祭�� ��㣨� ॣ�� etc); 
XTG_REGS_CURV_STRUCT		ends
;--------------------------------------------------------------------------------------------------------
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
;�������� ��� ������ xTG;
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 



;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
;�����⨬� ���祭�� ��� ���� XTG_TRASH_GEN.fmode (०�� �����樨 ����); 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
XTG_MASK			equ		00000000b									;00h (��������, �� ᥩ�� �� ���祭�� != 1 - �㤥� ������� ��� XTG_MASK); 
XTG_REALISTIC		equ		00000001b									;01h 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
;�����⨬� ���祭�� ��� ���� XTG_TRASH_GEN.fmode (०�� �����樨 ����); 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 



;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
;�����⨬� ���祭�� ��� ���� XTG_TRASH_GEN.fregs (������ ॣ�); 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
XTG_EAX				equ		00000001b									;01h
XTG_ECX				equ		00000010b									;02h
XTG_EDX				equ		00000100b									;04h
XTG_EBX				equ		00001000b									;08h
XTG_ESP				equ		00010000b									;10h
XTG_EBP				equ		00100000b									;20h
XTG_ESI				equ		01000000b									;40h
XTG_EDI				equ		10000000b									;80h 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
;�����⨬� ���祭�� ��� ���� XTG_TRASH_GEN.fregs (������ ॣ�����); 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 



;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
;䫠�� ��᮪ XTG_TRASH_GEN.xmask1 & XTG_TRASH_GEN.xmask2  
;�� ���� �� (祬 ����, ���� ����� ��������� �ਢ離� - � �� �㩭�); 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

;=====================================[��� ������ XTG_MASK]==============================================
;----------------------------------------[XMASK1 BEGIN]--------------------------------------------------
XTG_INC_DEC___R32										equ		00000000000000000000000000000001b	;01		;������� ࠧ����� ������権/�������権; 
XTG_NOT_NEG___R32										equ		00000000000000000000000000000010b	;02
XTG_MOV_XCHG___R32__R32									equ		00000000000000000000000000000100b	;03
XTG_MOV_XCHG___R8__R8_IMM8								equ		00000000000000000000000000001000b 	;04
XTG_MOV_R32_R16__IMM32_IMM16							equ		00000000000000000000000000010000b	;05
XTG_LEA___R32___MSO										equ		00000000000000000000000000100000b	;06
XTG_ADC_ADD_AND_OR_SBB_SUB_XOR___R32_R16__R32_R16		equ		00000000000000000000000001000000b	;07
XTG_ADC_ADD_AND_OR_SBB_SUB_XOR___R8__R8					equ		00000000000000000000000010000000b	;08
XTG_ADC_ADD_AND_OR_SBB_SUB_XOR___R32__IMM32				equ		00000000000000000000000100000000b	;09
XTG_ADC_ADD_AND_OR_SBB_SUB_XOR___R32__IMM8				equ		00000000000000000000001000000000b	;10
XTG_ADC_ADD_AND_OR_SBB_SUB_XOR___R8__IMM8				equ		00000000000000000000010000000000b	;11
XTG_RCL_RCR_ROL_ROR_SHL_SHR___R32__IMM8					equ		00000000000000000000100000000000b	;12
XTG_PUSH_POP___R32___R32								equ		00000000000000000001000000000000b	;13
XTG_PUSH_POP___IMM8___R32								equ		00000000000000000010000000000000b	;14
XTG_CMP___R32__R32										equ		00000000000000000100000000000000b	;15
XTG_CMP___R32__IMM8										equ		00000000000000001000000000000000b	;16
XTG_CMP___R32__IMM32									equ		00000000000000010000000000000000b	;17
XTG_TEST___R32_R8__R32_R8								equ		00000000000000100000000000000000b	;18
XTG_JXX_SHORT_DOWN___REL8								equ		00000000000001000000000000000000b	;19
XTG_JXX_NEAR_DOWN___REL32								equ		00000000000010000000000000000000b	;20
XTG_JXX_UP___REL8___REL32								equ		00000000000100000000000000000000b	;21
XTG_JMP_DOWN___REL8___REL32								equ		00000000001000000000000000000000b	;22
XTG_CMOVXX___R32__R32									equ		00000000010000000000000000000000b	;23
XTG_BSWAP___R32											equ		00000000100000000000000000000000b	;24
XTG_THREE_BYTES_INSTR									equ		00000001000000000000000000000000b	;25
XTG_MOV___R32_M32__M32_R32								equ		00000010000000000000000000000000b	;26
XTG_MOV___M32__IMM8_IMM32								equ		00000100000000000000000000000000b	;27
XTG_MOV___R8_M8__M8_R8									equ		00001000000000000000000000000000b	;28
XTG_INC_DEC___M32										equ		00010000000000000000000000000000b	;29
XTG_ADC_ADD_AND_OR_SBB_SUB_XOR___R32__M32				equ		00100000000000000000000000000000b	;30
XTG_ADC_ADD_AND_OR_SBB_SUB_XOR___M32__R32				equ		01000000000000000000000000000000b	;31
XTG_ADC_ADD_AND_OR_SBB_SUB_XOR___R8_M8__M8_R8			equ		10000000000000000000000000000000b	;32
;----------------------------------------[XMASK1 END]----------------------------------------------------
;----------------------------------------[XMASK2 BEGIN]--------------------------------------------------
XTG_ADC_ADD_AND_OR_SBB_SUB_XOR___M32_M8__IMM32_IMM8		equ		00000000000000000000000000000001b	;33 01
XTG_CMP___R32_M32__M32_R32								equ		00000000000000000000000000000010b	;34 02
XTG_CMP___M32_M8__IMM32_IMM8							equ		00000000000000000000000000000100b	;35 03
XTG_MOV_LEA___R32__M32EBPO8								equ		00000000000000000000000000001000b	;36 04
XTG_MOV___M32EBPO8__R32									equ		00000000000000000000000000010000b	;37 05
XTG_MOV___M32EBPO8__IMM32								equ		00000000000000000000000000100000b	;38 06
XTG_ADC_ADD_AND_OR_SBB_SUB_XOR___R32__M32EBPO8			equ		00000000000000000000000001000000b	;39 07
XTG_ADC_ADD_AND_OR_SBB_SUB_XOR___M32EBPO8__R32			equ		00000000000000000000000010000000b	;40	08
XTG_ADC_ADD_AND_OR_SBB_SUB_XOR___M32EBPO8__IMM32_IMM8	equ		00000000000000000000000100000000b	;41 09
XTG_CMP___R32_M32EBPO8__M32EBPO8_R32					equ		00000000000000000000001000000000b	;42 10
XTG_CMP___M32EBPO8__IMM32_IMM8							equ		00000000000000000000010000000000b	;43 11 

XTG_MASK_WINAPI											equ		00000000000000000000100000000000b	;44 12 
;----------------------------------------[XMASK2 END]----------------------------------------------------
;=====================================[��� ������ XTG_MASK]==============================================

;===================================[��� ������ XTG_REALISTIC]===========================================
;----------------------------------------[XMASK1 BEGIN]--------------------------------------------------
XTG_FUNC												equ		00000000000000000000000000000001b	;������� �㭪権 (� �஫�����, ���襬, ��������� etc); 
XTG_REALISTIC_WINAPI									equ		00000000000000000000000000000010b	;������� ����-������; 
XTG_LOGIC												equ		00000000000000000000000000000100b	;�� ������ ��� �����樨 ����; 
;----------------------------------------[XMASK1 END]----------------------------------------------------
;===================================[��� ������ XTG_REALISTIC]===========================================

;------------------------------------------[XMASK]-------------------------------------------------------
XTG_ON_XMASK											equ		11111111111111111111111111111111b	;01
XTG_OFF_XMASK											equ		00000000000000000000000000000000b	;02
;------------------------------------------[XMASK]-------------------------------------------------------
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
;䫠�� ��᮪ XTG_TRASH_GEN.xmask1 & XTG_TRASH_GEN.xmask2  
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
 


;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
;�����⨬� ���祭�� ��� ���� XTG_DATA_STRUCT.xmask (��᪠ ��� �����樨 ������); 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
XTG_DG_STRA												equ		00000000000000000000000000000001b
XTG_DG_NUM32											equ		00000000000000000000000000000010b
XTG_DG_ON_XMASK											equ		00000000000000000000000000000011b
XTG_DG_OFF_XMASK										equ		00000000000000000000000000000000b
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
;�����⨬� ���祭�� ��� ���� XTG_DATA_STRUCT.xmask (��᪠ ��� �����樨 ������); 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
  


;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
;�����⨬� ���祭�� ��� ���� XTG_DATA_STRUCT.rdata_pva (����); 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
XTG_OFFSET_ADDR											equ		00h		;���� � rdata_addr - ��᮫��� 䨧��᪨� � 䠩��;
XTG_VIRTUAL_ADDR										equ		01h 	;����㠫�� ���� � ����� (VirtualAddress aka VA); 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
;�����⨬� ���祭�� ��� ���� XTG_DATA_STRUCT.rdata_pva (����);
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 



;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
;䫠�� ��� ���� XTG_INSTR_DATA_STRUCT.param_1
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
XTG_XIDS_CONSTR											equ		10000000000000000000000000000000b	;������砥�, �� �� ����ਬ ������� ��� �������樨 (push/pop etc);  
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
;䫠�� ��� ���� XTG_INSTR_DATA_STRUCT.param_1
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 



;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
;�����⨬� ���祭�� ��� ���� XTG_INSTR_PARS_STRUCT.flags
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
XTG_VL_INSTR_INIT										equ		00000000000000000000000000000001b	;����� 䫠� ����砥�, �� ࠧ��࠭��� ������� - �� ������� ���樠����樨 (mov reg32, reg32   etc); 
XTG_VL_INSTR_CHG										equ		00000000000000000000000000000010b	;������� ��������� ��ࠬ���(��) (add reg32, reg32 etc); 
XTG_VL_P1_REG											equ		00000000000000000000000000000100b	;���� ��ࠬ���_1, � �� ॣ����
XTG_VL_P1_ADDR											equ		00000000000000000000000000001000b	;param_1 - ����
XTG_VL_P1_NUM											equ		00000000000000000000000000010000b	;��� �᫮
XTG_VL_P1_GET											equ		00000000000000000000000000100000b	;��ࠬ_1 ����砥� ���祭�� (add reg32_1, reg32_2 -> reg32_1 - ॣ����, ����砥� ���祭��, reg32_2 -> ॣ, �⤠�� ���祭��); 
XTG_VL_P1_GIVE											equ		00000000000000000000000001000000b	;param_1 �⤠�� ���祭��
XTG_VL_P2_REG											equ		00000000000000000000000010000000b	;���� ��ࠬ_2, � �� ॣ
XTG_VL_P2_ADDR											equ		00000000000000000000000100000000b	;��� ����
XTG_VL_P2_NUM											equ		00000000000000000000001000000000b	;��� �᫮
XTG_VL_P2_GET											equ		00000000000000000000010000000000b	;��ࠬ_2 ����砥� ���祭��
XTG_VL_P2_GIVE											equ		00000000000000000000100000000000b	;�⤠�� ���祭��; 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
;�����⨬� ���祭�� ��� ���� XTG_INSTR_PARS_STRUCT.flags
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 



;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
;�������⥫�� ���祭�� ��� ���� XTG_INSTR_DATA_STRUCT.flags;
;�᭮��� �� ���祭�� - �� �����, ᮮ�-騥 ������� 䫠��� �������権; 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
XTG_ID_FUNC_PROLOG										equ		1001	;����砥�, �� �� �㦭� ����㫨�� � �஢���� �஫�� ��襩 �㭪�
XTG_ID_FUNC_PARAM										equ		1002	;�஢�ઠ ⮫쪮 �� ᣥ��७���� �室�饣� ��ࠬ��� 
XTG_ID_FUNC_CALL										equ		1003	;������ call'a
XTG_ID_FUNC_EPILOG										equ		1004	;������ ������� (+ ������� ret); 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
;�������⥫�� ���祭�� ��� ���� XTG_INSTR_DATA_STRUCT.flags;
;�᭮��� �� ���祭�� - �� �����, ᮮ�-騥 ������� 䫠��� �������権; 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 


 