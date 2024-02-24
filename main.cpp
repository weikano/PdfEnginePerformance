//#include <QCoreApplication>
#include <iostream>
#include "pdfiumrenderer.h"
#include "MuPdfRenderer.h"
#include <string>
#include <vector>
#include <algorithm>

#include <chrono>



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
    files.push_back("/home/roman/git/PdfEnginePerformance/testpdf/冠状动脉血栓抽吸临床应用专家共识.pdf");

    for(const auto& file:files)
    {
        renderer->openDocument(file.c_str(), "");
        int pageCount = renderer->getPageCount();
        std::cout<<"pageCount:"<<pageCount<<std::endl;
        for(int i=0;i<pageCount;i++)
        {
            renderer->render(i);
        }
        renderer->closeDocument();
    }
}

static void testmultitimes(PdfRenderer* renderer, const char* prefix, int times)
{
    auto starttime = std::chrono::system_clock::now();
    std::cout<<prefix<<" start"<<std::endl;
    for(int i=0;i<times;i++) {
        test1(renderer, prefix);
    }

    std::chrono::duration<double> diff = std::chrono::system_clock::now() - starttime;
    std::cout<<prefix<<", "<<"time cost :"<<diff.count()<<std::endl;
}

int main(int argc, char *argv[])
{
    PdfRenderer* mupdf = new MuPdfRenderer();
    PdfRenderer* pdfium = new PdfiumRenderer();

//    testmultitimes(mupdf, "mupdf",2);
    testmultitimes(pdfium,"pdfium", 1);

    delete mupdf;
    delete pdfium;

    return 0;
}
