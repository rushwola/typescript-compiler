#include <iostream>
#include <string>
#include <cstring>
#include "mtools.h"
#include "config.h"

/**
 * 程序运行模式
 */
enum RunningMode{astWalker,  //AST解释器
                vm,          //字节码虚拟机
                dumpAsm,     //输出汇编代码
                dumpIR,      //显示生成的IR
                dumpBC,      //输出字节码
                help         //显示帮助信息
                }
;

/**
 * 命令行参数的选项
 */
class CommandArgs{
    public:
    RunningMode mode = RunningMode::astWalker;  //运行模式
    
    std::string fileNameWithoutPostfix = NULL;     //文件名称，不带后缀的版本
    std::string fileName = NULL;     //文件名称，可以是.ts或.bc

    bool verbose = false;         //显示详细的调试信息
}
;

// void compileAndRun(CommandArgs *);

void showHelp(){
    std::cout << "一个简单的TypeScript编译器和解释器 "<< std::endl;
    std::cout << "使用:\tnode play (-B|--dumpBC|--dumpAsm)? (-v)? FileName"<< std::endl;
    std::cout << "\t node play --help"<< std::endl;
    std::cout << "举例："<< std::endl;
    std::cout << "\tnode play example.ts -> 用AST解释器执行example.ts"<< std::endl;
    std::cout << "\tnode play example.bc -> 用字节码虚拟机执行example.bc"<< std::endl;
    std::cout << "\tnode play -B example.ts -> 编译成字节码执行"<< std::endl;
    std::cout << "\tnode play --dumpBC example.ts -> 编译成字节码执行，并保存到.bc文件中"<< std::endl;
    std::cout << "\tnode play --dumpAsm example.ts -> 编译成汇编代码，保存到.s文件中"<< std::endl;
    std::cout << "\tnode play --dumpIR example.ts -> 以Dot格式生成IR图"<< std::endl;

    std::cout << "可选参数："<< std::endl;
    std::cout << "\t-B:\t用字节码虚拟机运行程序。缺省用AST解释器执行程序。"<< std::endl;
    std::cout << "\t--dumpBC:\t编译成字节码，保存到.bc文件中。"<< std::endl;
    std::cout << "\t--dumpAsm:\t编译成x86_64的汇编代码，保存到.s文件中。"<< std::endl;
    std::cout << "\t--dumpIR:\t以Dot格式生成IR图。"<< std::endl;
    std::cout << "\t-v:\t显示编译过程中的详细信息。"<< std::endl;
    std::cout << "\t--help:\t显示当前的帮助信息。"<< std::endl;

    std::cout << "FileName："<< std::endl;
    std::cout << "\t文件后缀可以是.ts或.bc，分别作为TypeScript和字节码文件读入。当文件后缀为.bc时，自动启动-B选项，用字节码虚拟机运行字节码文件。"<< std::endl;
}
;


/**
 * 解析命令行参数
 */
CommandArgs * parseCommandArgs(int argc, char* argv[]){
    CommandArgs *args = new CommandArgs();

    if (argc < 3) {
        std::cout << "请输入文件名称。" << std::endl;
        std::cout << "用\"node play --help\"来显示更多帮助信息。" << std::endl;
        return nullptr;
    }

    int modeCount = 0;  //出现了几次mode参数？
    for (int i = 2; i < argc; i++){
        char* arg = argv[i];
        if (strcmp(arg,"-B")==0){
            args->mode = RunningMode::vm;
            modeCount++;
        }
        else if (strcmp(arg,"--dumpAsm")==0){
            args->mode = RunningMode::dumpAsm;
            modeCount++;
        }
        else if (strcmp(arg,"--dumpIR")==0){
            args->mode = RunningMode::dumpIR;
            modeCount++;
        }
        else if (strcmp(arg,"--dumpBC")==0 ){
            args->mode = RunningMode::dumpBC;
            modeCount++;
        }
        else if (strcmp(arg,"--help")==0){
            args->mode = RunningMode::help;
            modeCount++;
        }
        else if (strcmp(arg,"-v")==0){
            args->verbose = true;
            CONFIG::verbose = true;
        }
        else{
            if(endsWith(arg,".ts") || endsWith(arg,".bc")){
                if (args->fileName.empty()){
                    std::cout << "输入了多个文件名。" << std::endl;
                    std::cout << "用\"node play --help\"来显示更多帮助信息。"<< std::endl;
                    return nullptr;
                }
                else{
                    args->fileName = arg;
                }
            }
            else{
                std::cout << "不认识的参数: " << arg << std::endl;
                std::cout << "用node play --help来显示更多帮助信息。"<< std::endl;
                return nullptr;
            }
        }
    }

    if (modeCount >1){
        std::cout << "使用了相互冲突的运行模式。" << std::endl;
        std::cout << "用\"node play --help\"来显示更多帮助信息。" << std::endl;
        return nullptr;
    }

    if (!args->fileName.empty()){
        args->fileNameWithoutPostfix = args->fileName.substr(0,args->fileName.length()-3);
    }
    else if (args->mode!=RunningMode::help){
        std::cout << "请输入文件名称。"<< std::endl;
        std::cout << "用\"node play --help\"来显示更多帮助信息。"<< std::endl;
        return nullptr;
    }

    return args;
}

/**
 * 解析命令行参数并运行
 */
// void execute(){
//     CommandArgs * args = parseCommandArgs();
//     if (&args == nullptr) return;
    
//     if (args->mode == RunningMode::help){
//         showHelp();
//     }
//     else{
//         compileAndRun(args);
//     }
// }
// ;

int main(int argc, char* argv[]) {
    std::cout << "Hello, World!" << std::endl;
    //解析命令行参数并运行
    CommandArgs * args = parseCommandArgs(argc,argv);
    if (&args == nullptr) return 0;
    
    if (args->mode == RunningMode::help){
        showHelp();
    }
    else{
        // compileAndRun(args);
    }

    return 0;
}
