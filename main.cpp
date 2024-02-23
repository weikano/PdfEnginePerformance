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
    files.push_back("/home/weikan/下载/冠状动脉血栓抽吸临床应用专家共识.pdf");

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

//    std::string directory = "/home/weikan/git/pdfium/testing/resources/";
//    std::vector<std::string> files;
//    files.push_back("about_blank.pdf");
//    files.push_back("annotation_highlight_long_content.pdf");
//    files.push_back("annotation_highlight_rollover_ap.pdf");
//    files.push_back("annotation_highlight_square_with_ap.pdf");
//    files.push_back("annotation_ink_multiple.pdf");
//    files.push_back("annotation_markup_multiline_no_ap.pdf");
//    files.push_back("annotation_stamp_with_ap.pdf");
//    files.push_back("annotiter.pdf");
//    files.push_back("annots.pdf");
//    files.push_back("bug_1058653.pdf");
//    files.push_back("bug_1768.pdf");
//    files.push_back("weblinks.pdf");
//    files.push_back("weblinks_across_lines.pdf");
//    files.push_back("two_signatures.pdf");
//    files.push_back("text_font.pdf");
//    files.push_back("tagged_table.pdf");
//    files.push_back("tagged_mcr_multipage.pdf");
//    files.push_back("tagged_marked_content.pdf");
//    files.push_back("tagged_actual_text.pdf");
//    files.push_back("rotated_image.pdf");
//    files.push_back("page_labels.pdf");
//    files.push_back("many_rectangles.pdf");

    PdfRenderer* mupdf = new MuPdfRenderer();
    PdfRenderer* pdfium = new PdfiumRenderer();

//    mupdf->openDocument("/home/weikan/文档/链接器和加载器.pdf", "");
//    pdfium->openDocument("/home/weikan/cropped_text.pdf", "");
//    int count = pdfium->getPageCount();
//    for(int i=1;i<count;i++) {
//        pdfium->render(i);
//    }

//    testmultitimes(pdfium, "pdfium", 2);
    testmultitimes(mupdf, "mupdf",2);

    delete mupdf;
    delete pdfium;
//    QCoreApplication a(argc, argv);

//    return a.exec();
}
