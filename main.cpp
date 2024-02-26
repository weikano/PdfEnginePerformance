//#include <QCoreApplication>
#include <iostream>
#include "pdfiumrenderer.h"
#include "MuPdfRenderer.h"
#include <string>
#include <vector>
#include <algorithm>

#include <chrono>
#include <filesystem>
namespace fs = std::filesystem;


static void test(PdfRenderer *renderer, std::string& dir, std::vector<std::string>& names)
{
    for(const auto& name:names)
    {
        std::string target = dir.append(name);
        renderer->openDocument(target.c_str(), "");
        int pageCount = renderer->getPageCount();
        std::cout<<"pageCount:"<<pageCount<<std::endl;
        for(int i=0;i<pageCount;i++)
        {
            renderer->render(i);
        }
        renderer->closeDocument();
    }
}

static void test1(PdfRenderer* renderer, const char* prefix)
{

    std::vector<std::string> files;
    for(const auto& entry : fs::directory_iterator(RESOURCE_DIR)) {
        files.push_back(entry.path());
    }

    for(const auto& file:files)
    {
        auto starttime = std::chrono::system_clock::now();
        std::cout<<"begin file: " << file<<std::endl;
        renderer->openDocument(file.c_str(), "");
        int pageCount = renderer->getPageCount();
        std::cout<<"pageCount:"<<pageCount<<std::endl;
        for(int i=0;i<pageCount;i++)
        {
            renderer->render(i);
        }
        renderer->closeDocument();
        std::chrono::duration<double> diff = std::chrono::system_clock::now() - starttime;
#ifdef USE_SKIA
    std::cout<<"SKIA_ENALED: ";
#else
    std::cout<<"SKIA_DISABLED: ";
#endif
        auto total = diff.count();
        std::cout<<"total time: "<<total<<", avg: "<< total/pageCount << std::endl;
        std::cout<<"end file========================"<<std::endl;
    }
}

static void testmultitimes(PdfRenderer* renderer, const char* prefix, int times)
{

    for(int i=0;i<times;i++) {
        test1(renderer, prefix);
    }  
}

int main(int argc, char *argv[])
{
//    PdfRenderer* mupdf = new MuPdfRenderer();
    PdfRenderer* pdfium = new PdfiumRenderer();    
//    testmultitimes(mupdf, "mupdf",2);
    testmultitimes(pdfium,"pdfium", 1);

//    delete mupdf;
    delete pdfium;

    return 0;
}
