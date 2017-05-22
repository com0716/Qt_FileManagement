#ifndef PAGE_H
#define PAGE_H

#include <QObject>
#include "global_header.h"

class Page : public QObject
{
    Q_OBJECT
public:
    explicit Page(QObject *parent = 0);
    unsigned int getPageSize() const;
    void setPageSize(unsigned int size);

    void setTotalCount(unsigned int count);

    unsigned int getCurrentPage() const;
    void setCurrentPage(unsigned int page);
    void currentPageAdd();

    unsigned int getMaxPage() const;

private:
    unsigned int pageSize; //每页显示的数据量，初始化为20

    unsigned int totalCount; //通过查询数据库获得，初始化为0
    unsigned int currentPage; //当前是第几页，是用户操作的结果，初始化为1
    unsigned int maxPage; //在设置totalCount的时候计算获得
};

#endif // PAGE_H
