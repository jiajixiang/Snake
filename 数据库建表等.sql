create database snake;
use snake;
desc user;
desc  game_record;
create table user(
    u_mac nvarchar(20) not null primary key,
    u_name nvarchar(20) not null
);
create table game_record(
    g_mac nvarchar(20) not null,
    g_name nvarchar(20) not null,
    g_ip nvarchar(20) not null,
    g_time nvarchar(50),
    g_score int not null
);

alter table game_record change g_mac g_mac nvarchar(20) not null;
desc game_record;
CREATE USER 'User'@'%' IDENTIFIED BY '123456'; 
GRANT SELECT, INSERT ON snake.user TO 'pig'@'%'; 
GRANT SELECT, INSERT ON snake.game_record TO 'pig'@'%'; 
GRANT SELECT,insert,update ON snake.ranking TO 'pig'@'%'; 
SELECT User, Host FROM mysql.user;
show grants for pig;

create table ranking(
	 r_mac nvarchar(20) not null,
	 r_name nvarchar(20) not null,
     r_time datetime not null,
     r_score int not null
);
desc ranking;
desc game_record;
use snake;
select * from user;
select * from game_record;
select r_name,r_time,r_score from ranking order by r_score desc;
select g_ip,g_time,g_score from game_record where g_mac='00:E0:4C:36:56:56';
select * from ranking;
select * from ranking where r_mac='00:E0:4C:36:56:56';
desc ranking;
delete from ranking;
delete from game_record;
delete from ranking where r_score=85655808;
;
update ranking set r_score=13,r_time='2017.12.15 03:02:42.261 周五' where r_mac='00:E0:4C:36:56:56';
update ranking set r_score=2 where r_mac='00:E0:4C:36:56:56';