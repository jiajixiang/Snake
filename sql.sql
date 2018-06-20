create database class_set;
use class_set;
show tables;
CREATE DATABASE IF NOT EXISTS xyesjy;
use xyesjy;
create table User(
	
	UserID nvarchar(5) not null primary key,
	UserPwd nvarchar(10) not null,
	UserName nvarchar(10) not null,
	UserSex nvarchar(8),
	UserAdd nvarchar(20) not null,
	PostCode nvarchar(10) not null,
	UserPhone char(15) not null,
	UserEmail nvarchar(25)
);
create table Bulletin(
	BulletinID tinyint(4) not null primary key,
	BulletinTitle nvarchar(10) not null,
	BulletinContent nvarchar(100),
	BulletPostTime datetime
);
create table GoodsInfo(
	GoodsID int(5) not null primary key AUTO_INCREMENT,
	GoodsName nvarchar(10) not null,
	GoodsCategory nvarchar(10) not null,
	GoodsImageURL nvarchar(50),
	GoodsNum tinyint(4) not null,
	GoodsPrice int(5) not null,
	GoodsOldNew nvarchar(10) not null,
	GoodsPayMode nvarchar(5) not null,
	GoodsDeliverMode nvarchar(10) not null,
	GoodsCarriage nvarchar(5),
	GoodsShelfTime Datetime not null,
	GoodsOwnerID nvarchar(5) not null,
	GoodsDetail nvarchar(20),
	foreign key(GoodsOwnerID) references User(UserID)
);
create table Manager(
	ManagerID nvarchar(5) not null primary key,
	ManagerPwd nvarchar(10) not null,
	ManagerName nvarchar(10) not null,
	ManagerSex char(2),
	ManagerAdd nvarchar(20) not null,
	ManagerPhone nvarchar(15) not null
);
INSERT INTO User VALUES ("66666", "66666","张三", "男","北京市","100000","155xxxx6666","xxxx@163.com");
select * from User;