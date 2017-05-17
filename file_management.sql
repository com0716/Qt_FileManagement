//创建数据库
CREATE DATABASES file_management;
USE file_management;

//创建admin表
CREATE TABLE admin(
id INT PRIMARY KEY AUTO_INCREMENT,
name VARCHAR(64) NOT NULL UNIQUE,
password VARCHAR(200) NOT NULL);

//创建guest表
CREATE TABLE guest(
name VARCHAR(64) PRIMARY KEY,
grade TINYINT NOT NULL,
password VARCHAR(200) NOT NULL
);

//手动添加数据
INSERT INTO admin (name, password) VALUES ("root", MD5("123"));
INSERT INTO admin (name, password) VALUES ("host", MD5("123"));
INSERT INTO admin (name, password) VALUES ("hhx1003", MD5("123"));
INSERT INTO admin (name, password) VALUES ("com0716", MD5("123"));
INSERT INTO admin (name, password) VALUES ("admmin", MD5("123"));

//手动添加数据
INSERT INTO guest (name, grade, password) VALUES ("xiaoming", 3, MD5("123"));
INSERT INTO guest (name, grade, password) VALUES ("lilei", 2, MD5("123"));


//创建文件表
CREATE TABLE file(
fpath VARCHAR(256) NOT NULL,
fname VARCHAR(256) NOT NULL,
fdesc VARCHAR(256),
date DATETIME PRIMARY KEY,
uploader VARCHAR(64) NOT NULL,
download_count INT NOT NULL,
size INT NOT NULL
);

INSERT INTO file (fpath, fname, fdesc, date, uploader, download_count, size)
VALUES ("root/file/", "hhx1003.txt", "hhx1003 is a boy", NOW(), "root", 0, 100);

