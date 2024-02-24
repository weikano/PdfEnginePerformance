#include "pdfiumrenderer.h"
#include "public/cpp/fpdf_scopers.h"
#include <malloc.h>
#include <iostream>
PdfiumRenderer::PdfiumRenderer()
{

    FPDF_InitLibrary();
}

PdfiumRenderer::~PdfiumRenderer()
{

    FPDF_DestroyLibrary();
}

void PdfiumRenderer::closeDocument()
{

    FPDF_CloseDocument(document);
}

void PdfiumRenderer::openDocument(const char *path, const char *pwd)
{

    document = FPDF_LoadDocument(path, pwd);
}

int PdfiumRenderer::getPageCount()
{

    return FPDF_GetPageCount(document);
}

struct rgb {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
};

void PdfiumRenderer::render(int pageIndex)
{    
    ScopedFPDFPage page(FPDF_LoadPage(document, pageIndex));
    FS_SIZEF size {0,0};
    FPDF_GetPageSizeByIndexF(document, pageIndex, &size);
    void* tmp = malloc(size.width * size.height * sizeof(rgb));
    ScopedFPDFBitmap bitmap(FPDFBitmap_CreateEx(size.width, size.height, FPDFBitmap_BGR, tmp, size.width * sizeof(rgb)));
    FPDFBitmap_FillRect(bitmap.get(), 0,0, size.width, size.height, 0xFFFFFF);
    FPDF_RenderPageBitmap(bitmap.get(), page.get(), 0,0, size.width, size.height, 0, FPDF_REVERSE_BYTE_ORDER | FPDF_ANNOT);
    free(tmp);
}

void PdfiumRenderer::showbox(int pageIndex)
{
    ScopedFPDFPage page(FPDF_LoadPage(document, pageIndex));
    float l, t, r, b;
    FPDFPage_GetCropBox(page.get(), &l, &b, &r, &t);
    printf("pdfium pageIndex:%d, cropbox(%f, %f, %f, %f)\n", pageIndex, l, t, r, b);
    FPDFPage_GetMediaBox(page.get(), &l, &b, &r, &t);
    printf("pdfium pageIndex:%d, mediabox(%f, %f, %f, %f)\n", pageIndex, l, t, r, b);
    FPDFPage_GetTrimBox(page.get(), &l, &b, &r, &t);
    printf("pdfium pageIndex:%d, trimbox(%f, %f, %f, %f)\n", pageIndex, l, t, r, b);
}
