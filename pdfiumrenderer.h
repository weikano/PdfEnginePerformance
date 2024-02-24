#ifndef PDFIUMRENDERER_H
#define PDFIUMRENDERER_H

#include "PdfRenderer.h"
#include "public/fpdf_doc.h"
class PdfiumRenderer : public PdfRenderer
{
public:
    PdfiumRenderer();
    ~PdfiumRenderer();
    void closeDocument() override;
    void openDocument(const char*, const char*) override;
    int getPageCount() override;
    void render(int pageIndex) override;
    void showbox(int pageIndex) override;
private:
    FPDF_DOCUMENT document;
};

#endif // PDFIUMRENDERER_H
