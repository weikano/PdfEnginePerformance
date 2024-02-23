#ifndef MUPDFRENDERER_H
#define MUPDFRENDERER_H
#include "PdfRenderer.h"
#include "mupdf/fitz.h"
class MuPdfRenderer : public PdfRenderer
{
public:
    MuPdfRenderer();
    ~MuPdfRenderer();
    void closeDocument() override;
    void openDocument(const char*, const char*) override;
    int getPageCount() override;
    void render(int pageIndex) override;
    void showbox(int pageIndex) override;
private:
    fz_context *context;
    fz_document *document;
};
#endif // MUPDFRENDERER_H
