.386p
.model flat
include exeption.inc
.DATA
include dinav2.inc
db '(c) Voodoo//SMF 07.07.2000'
extrn   MessageBeep:PROC  ; ���쪮 ���� ��� ⮣� �⮡� �ண� ����᪠����.
                          ; ��� ���o�⮢ �ண� �� ����᪠��� � �32 �����.
;-----------------------------------------------------------------------------
MyCode:
; � ��।��� �ࠢ����� DINA v2.2
; ��� ࠡ�⠥� � �⥪�.
           call @MyCodeL1
@Hello:      db 'Hello from stack !!!',0
@MyCodeL1:   pop ebx

             xor edi,edi            ;
             call Kern32VxInit      ; ���樠������ VX ��୥�� (KERNEL32.dll)

             ; ����稬  User32Hahdler
             call LpL
@UserName    db 'USER32.dll',0
LpL:
             callEx GetModuleHandleA ; �맮� GetModuleHandleA
                                     ; � �⥪� offset �� USER32.DLL
             mov edi,eax             ; edi=ImageBaseVA of User32.dll
             ;-------------
             xor eax,eax             ; ������ �� ����饣� ��ࠡ��稪� SEH
             pop dword ptr  fs:[eax] ;
             pop eax                 ;
             ;-------------
             call Kern32VxInit ; ���樠������ VX ��୥�� �� ��� User32.dll

             push 0
             push ebx
             push ebx
             push 0
             callEx MessageBoxA
            ;-------------
             xor eax,eax
             pop dword ptr  fs:[eax]
             pop eax
            ;-------------
             xor edi,edi
             call Kern32VxInit   ; ���樠������ VX ��୥�� ��� KERNEL32.dll

             push 0              ; ��室 �� �ண�.
             callEx ExitProcess
;-----------------------------------------------------------------------------
include kern32vx.inc
;-----------------------------------------------------------------------------
EndMyCode:
.data?
buffer db 1024 dup(?)
.CODE
MyCodeSize equ offset EndMyCode- offset MyCode
KernVX32:
    mov eax,MyCodeSize
    xor edi,edi
    call Kern32VxInit      ; ���樠������ VX ��୥�� (KERNEL32.dll)
   ;--------------------
   ; ������ Randomaze
    push offset buffer
    callEx GetSystemTime  ; �맮� GetSystemTime
    mov RandSeed,eax
   ;-----------------
   ; �뤥�塞 ������ ��� �����樨 ����
    push MyCodeSize*10 ; K<=10
    push 0
    callEx GlobalAlloc
    push eax
    callEx GlobalLock
    ;-------------------
    mov edi,eax            ;edi=���饭�� �� ��� ����
    mov esi,offset MyCode  ;esi=��� ��� ����� �� "�������䨬"
    mov ecx,MyCodeSize     ;ecx=��� ࠧ���
    xor edx,edx            ;edx=���饭�� �� ����� �������  
    push 00050005h         ;DWORD=(WORD NopsMaxCount, WORD MycopMaxCount)  
    call MakePolyImg       ;�� ��室� eax=������ ᣥ���஢������ ����
    ;--------------------
    xor eax,eax  ; �����⠫�� VX ��୥�
    pop dword ptr fs:[eax] ;
    pop eax      ;
    jmp edi      ; �⤠�� �ࠢ����� ᣥ���஢������ ����.
                 ;
    push 0
    callEx ExitProcess
exit_:
Ends
End KernVX32

