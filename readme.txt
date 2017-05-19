程序开发记录
2017/5/17 13:52:20
1 mysql表的设计
    三个表：管理员表 访客表 文件表
    1.1 管理表
        id
        name
        password：使用MD5加密存储
    1.2 访客表
        name
        grade
        password
    1.3 文件表
        date：文件上传时间
        name：文件名词
        desc：文件描述
        path：文件路径
        uploader：上传者（name）
        download_count：下载次数

2 管理员-界面设计
    2.1 登录界面
        用户名
        密码
    2.2 管理界面
        2.2.1 管理菜单
            查看访客表
            查看文件表

            退出
        2.2.2 操作菜单
            访客表的增删改查
            文件表的增删改查
        2.2.3 窗口菜单行为
            层叠
        2.2.4 帮助菜单
            帮助
            关于
3 文件表修改 2017/5/19 13:51:27
fid：文件编号,由时间和上传这编号构成
fname：文件名，保留文件上传的名字
fdesc：文件描述，简要说明文件的作用
ftype：文件类型，保留项，可以做为以后的扩展
fsize：文件大小
fdate：文件上传时间
uploader：文件上传者
download_count:文件下载次数

CREATE TABLE file_blob(
fid VARCHAR(20) NOT NULL PRIMARY KEY,
fname VARCHAR(40) NOT NULL,
fdesc VARCHAR(256),
fsize INT NOT NULL,
fdate DATETIME NOT NULL,
uploader VARCHAR(64) NOT NULL,
download_count INT NOT NULL,
fsrc MEDIUMBLOB NOT NULL
);



