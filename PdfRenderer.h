#ifndef PDFRENDERER_H
#define PDFRENDERER_H
class PdfRenderer
{
public:
    ~PdfRenderer(){};
    virtual void openDocument(const char *path, const char *pwd) = 0;
    virtual int getPageCount() = 0;
    virtual void render(int pageIndex) = 0;
    virtual void closeDocument() = 0;
    virtual void showbox(int pageIndex) = 0;
};
#endif // PDFRENDERER_H
