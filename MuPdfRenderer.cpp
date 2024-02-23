#include "MuPdfRenderer.h"
#include <iostream>

#include "mupdf/fitz/buffer.h"

MuPdfRenderer::MuPdfRenderer()
{
    std::cout<<__FUNCTION__<<std::endl;
    context = fz_new_context(NULL, NULL, FZ_STORE_DEFAULT);
    fz_register_document_handlers(context);
}

MuPdfRenderer::~MuPdfRenderer()
{
    fz_drop_context(context);
}

void MuPdfRenderer::closeDocument()
{    
    fz_drop_document(context,document);
}

void MuPdfRenderer::openDocument(const char *path, const char *pwd)
{    
    document = fz_open_document(context, path);
}

int MuPdfRenderer::getPageCount()
{    
    return fz_count_pages(context, document);
}

void MuPdfRenderer::render(int pageIndex)
{    
    fz_page* page = NULL;
    fz_pixmap *pix = NULL;
    fz_matrix ctm = fz_identity;
    fz_device* device = NULL;
    fz_rect bbox;
    int x, y;
    fz_try(context)
    {
        page = fz_load_page(context, document, pageIndex);
        fz_new_pixmap_from_page_number(context, document, pageIndex, ctm, fz_device_rgb(context), 0);
        for (y = 0; y < pix->h; ++y)
            {
                unsigned char *p = &pix->samples[y * pix->stride];
                for (x = 0; x < pix->w; ++x)
                {
                    if (x > 0)
                        printf("  ");
                    printf("%3d %3d %3d", p[0], p[1], p[2]);
                    p += pix->n;
                }
                printf("\n");
            }
    }
    fz_always(context)
    {
        fz_drop_pixmap(context,pix);
        fz_drop_page(context, page);
    }
    fz_catch(context)
    {

    }


}

void MuPdfRenderer::showbox(int pageIndex)
{
    fz_page* page = NULL;
    fz_try(context)
    {
        page = fz_load_page(context, document, pageIndex);
        fz_rect ret = fz_bound_page_box(context, page, FZ_CROP_BOX);
        printf("mupdf pageIndex:%d, cropbox(%f, %f, %f, %f)\n", pageIndex, ret.x0, ret.y0, ret.x1, ret.y1);
        ret = fz_bound_page_box(context,page, FZ_MEDIA_BOX);
        printf("mupdf pageIndex:%d, mediabox(%f, %f, %f, %f)\n", pageIndex, ret.x0, ret.y0, ret.x1, ret.y1);
        ret = fz_bound_page_box(context,page, FZ_TRIM_BOX);
        printf("mupdf pageIndex:%d, trimbox(%f, %f, %f, %f)\n", pageIndex, ret.x0, ret.y0, ret.x1, ret.y1);
    }
    fz_always(context)
    {
        fz_drop_page(context,page);
    }
    fz_catch(context) {

    }

}
