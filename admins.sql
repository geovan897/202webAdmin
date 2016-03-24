drop table if exists admins;
create table admins
  (
    AdminId INT(11) primary key auto_increment,
    AdminName varchar(32),
    AdminPW   varchar(64),
    activeSession varchar(128),
    firstLogin datetime,
    lastLogin  datetime
  );

