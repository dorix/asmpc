#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    int cancompile(0); //Droits
    int cancopy(0);
    int appel_sys(80); //Syscalls
    int printcall(4);
    int readcall(3);
    int exitcall(1);
    string fichierasmp("main.asmp"); //fichiers
    string fichierasm("main.asm");
    string curLine; //lignes en cours
    string curAsmLine;
    if (1)
    {
    cout << "Name of file to compile : " << endl;
    getline(cin, fichierasmp);
    fichierasmp = fichierasmp + ".asmp";
    cout << "Name of compilated file : " << endl;
    getline(cin, fichierasm);
    fichierasm = fichierasm + ".asm";
    cout << endl;
    cout << "Syscall interruption : " << appel_sys << endl;
    cout << "Exit\tsyscall : " << exitcall << endl;
    cout << "Read\tsyscall : " << readcall << endl;
    cout << "Print\tsyscall : " << printcall << endl;
    cout << "Asmp file : " << fichierasmp << endl;
    cout << "Asm file : " <<fichierasm << endl;
    }
    ifstream asmpFile(fichierasmp.c_str());
    ofstream asmFile(fichierasm.c_str());
    if(asmpFile && asmFile)
    {
        cancompile = 1;
        cout << "\nCompiling : \n" << endl;
        while(getline(asmpFile,curLine) && cancompile == 1)
        {
            cout << curLine <<endl;

            std::size_t pos = curLine.find("§"); // Sections
            if(pos==0)
            {
            curAsmLine = "SECTION ";
            curAsmLine = curAsmLine+curLine.substr(pos+2);
            asmFile << curAsmLine << endl;
            string codesec = "SECTION  .text";
            if(curAsmLine.compare(codesec) == 0)
            {
                curAsmLine = "global _main";
                asmFile << curAsmLine << endl;
            }
            }
            //---------------------------------------------//
            pos = curLine.find("text"); // varibles texte
            if(pos==0)
            {
            pos = 5;
            std::size_t texpos = curLine.find('"');
            string textvar = curLine.substr(pos,texpos-pos);
            curAsmLine = textvar+"db ";
            curAsmLine = curAsmLine+curLine.substr(texpos)+",0x0";
            asmFile << curAsmLine << endl;
            curAsmLine = "len"+textvar+"equ $-"+textvar;
            curAsmLine = curAsmLine.substr(0, curAsmLine.find_last_of(':'));
            asmFile << curAsmLine << endl;
            }
            //---------------------------------------------//
            pos = curLine.find("?"); // fonctions
            if(pos==0)
            {
            curAsmLine = "_"+curLine.substr(2)+":";
            asmFile << curAsmLine << endl;
            }
            //---------------------------------------------//
            pos = curLine.find("print"); // print
            if(pos==0)
            {
            string textvar = curLine.substr(6);
            asmFile << "mov eax,4" << endl;
            asmFile << "mov ebx,1" << endl;
            asmFile << "mov eax," << textvar << endl;
            asmFile << "mov eax,len" << textvar << endl;
            asmFile << "int 0x80" << endl;
            }
            //---------------------------------------------//
            pos = curLine.find("exit"); // exit
            if(pos==0)
            {
            asmFile << "mov eax,1" << endl;
            asmFile << "mov ebx,0" << endl;
            asmFile << "int 0x80" << endl;
            }
        }
    }
    else
    {
        cout << "Error : can't open asmp file, please check if this file exist, or if it have the read right for the compiler" << endl;
        return 0;
    }
    return 0;
}
