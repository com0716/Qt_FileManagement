#include "page.h"
#include <QtMath>

Page::Page(QObject *parent) : QObject(parent)
{
    this->pageSize = 2;
    this->totalCount = 0;
    this->currentPage = 1;
    this->maxPage = 0;
}

unsigned int Page::getPageSize() const
{
    return this->pageSize;
}

void Page::setPageSize(unsigned int size)
{
    this->pageSize = size;

    //更新
    //ps. 没有使用float强转之前是int运算获得的少一页，所以使用float强转
    this->maxPage = ceil((float)this->totalCount/this->pageSize);

    //改变pageSize之后，就能出现当前页大于最大页的情况
    if (this->currentPage > this->maxPage)
    {
        this->currentPage = this->maxPage;
    }
}

void Page::setTotalCount(unsigned int count)
{
    this->totalCount = count;
    //更新
    this->maxPage = ceil((float)this->totalCount/this->pageSize);

    //在进行删除操作时，就能出现当前页大于最大页的情况
    if (this->currentPage > this->maxPage)
    {
        this->currentPage = this->maxPage;
    }
}

unsigned int Page::getCurrentPage() const
{
    return this->currentPage;
}

void Page::setCurrentPage(unsigned int page)
{
    if (page > this->maxPage)
        this->currentPage = this->maxPage;
    else if (page <= 0)
        this->currentPage = 1;
    else
        this->currentPage = page;
}

void Page::currentPageAdd()
{
    if (this->currentPage < this->maxPage)
        this->currentPage ++;
}

unsigned int Page::getMaxPage() const
{
    return this->maxPage;
}


