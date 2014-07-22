/**
 * maize.skihat.cn
 */

# 创建数据库
CREATE DATABASE 'fruit' DEFAULT CHARACTER SET utf8;

# 使用数据库。
USE fruit;

# 创建商品数据表；
CREATE TABLE goods_category (
  `id`          INT          NOT NULL AUTO_INCREMENT PRIMARY KEY COMMENT  '主键',
  `name`        VARCHAR(32)  NOT NULL COMMENT '分类名称',
  `pinyin`      VARCHAR(32)  NOT NULL COMMENT '拼音码',
  `description` VARCHAR(256) NOT NULL DEFAULT '说明'
) ENGINE = innodb;

CREATE TABLE goods (
  `id`          INT           NOT NULL AUTO_INCREMENT PRIMARY KEY COMMENT '主键',
  `name`        VARCHAR(32)   NOT NULL COMMENT '商品名称',
  `thumb`       VARCHAR(64)   NOT NULL DEFAULT '' COMMENT '缩略图',
  `offer`       TINYINT (1)   NOT NULL DEFAULT 0 COMMENT '推荐',
  `home`        TINYINT (1)   NOT NULL DEFAULT 0 COMMENT '首页',
  `sale`       TINYINT (1)   NOT NULL DEFAULT 1 COMMENT  '上架',
  `price`       DECIMAL(8, 2) NOT NULL COMMENT '单价',
  `unit`        VARCHAR(8)    NOT NULL COMMENT '单位',
  `created`     INT           NOT NULL COMMENT '上架时间',
  `modified`    INT           NOT NULL COMMENT '最后更新时间',
  `description` VARCHAR(256)  NOT NULL DEFAULT '' COMMENT '说明',
  `category`    INT           NOT NULL COMMENT  '分类'
) ENGINE = innodb;

CREATE TABLE goods_detail (
  `id`     INT  NOT NULL AUTO_INCREMENT PRIMARY KEY COMMENT '主键',
  `goods`  INT  NOT NULL COMMENT '商品编号',
  `detail` TEXT NOT NULL COMMENT '详细内容'
) ENGINE = innodb;

# 附加外键引用
ALTER TABLE goods ADD FOREIGN KEY (category) REFERENCES goods_category (id);
ALTER TABLE goods_detail ADD FOREIGN KEY (goods) REFERENCES goods (id);




# 系统管理员
CREATE TABLE admins_user(
  `id`                    INT NOT NULL AUTO_INCREMENT PRIMARY KEY COMMENT '主键',
  `name`                  VARCHAR(16) NOT NULL COMMENT '用户名',
  `password`              VARCHAR(64) NOT NULL COMMENT '密码',
  `allow_access`          SMALLINT(1) NOT NULL COMMENT '允许访问',
  `created`               INT NOT NULL COMMENT '创建时间',
  `login_count`           SMALLINT NOT NULL DEFAULT 0 COMMENT '登录次数',
  `login_lasted_date`     INT NOT NULL COMMENT '最后登录时间',
  `login_lasted_address`  CHAR(16) NOT NULL COMMENT '最后登录地址',
  `description`           VARCHAR(128) NOT NULL DEFAULT '' COMMENT '说明'
) ENGINE = innodb;

# 会员用户
CREATE TABLE ucenter_user (
  `id`                    INT NOT NULL AUTO_INCREMENT PRIMARY KEY COMMENT '主键',
  `name`                  VARCHAR(16) NOT NULL COMMENT '用户名',
  `email`                 VARCHAR(64) NOT NULL COMMENT '电子邮件',
  `allow_access`          TINYINT(1)  NOT NULL DEFAULT 1 COMMENT '允许访问？',
  `password`              VARCHAR(128) NOT NULL DEFAULT '' COMMENT  '密码',
  `security_salt`         VARCHAR(32)  NOT NULL DEFAULT '' COMMENT '安全码',
  `created`               INT NOT NULL COMMENT '创建时间',
  `login_count`           SMALLINT NOT NULL DEFAULT 0 COMMENT '登录次数',
  `login_lasted_date`     INT NOT NULL DEFAULT 0 COMMENT  '最后登录时间',
  `login_lasted_address`  VARCHAR(16) NOT NULL DEFAULT '' COMMENT '最后登录地址'
) ENGINE  = innodb;

# 订单
CREATE TABLE `order` (
  `id`                  INT NOT NULL AUTO_INCREMENT  PRIMARY KEY COMMENT  '主键',
  `user`                INT NOT NULL COMMENT '会员编号',
  `status`              TINYINT(1) NOT NULL DEFAULT 1 COMMENT '订单状态：1.未处理、2：已配送、3：已完成、4：已取消',
  `telephone`           VARCHAR(16) NOT NULL DEFAULT '' COMMENT '联系电话',
  `shopping_date`       INT NOT NULL DEFAULT 0 COMMENT '配送时间',
  `consignee`           VARCHAR(8)  NOT NULL DEFAULT '' COMMENT '收货人',
  `consignee_address`   VARCHAR(32) NOT NULL DEFAULT '' COMMENT '收货地址',
  `consignee_date`      INT NOT NULL DEFAULT 0 COMMENT '收货时间',
  `created`             INT NOT NULL COMMENT '创建时间',
  `modified`            INT NOT NULL COMMENT '最后处理时间',
  `total`               DECIMAL(10,2) NOT NULL COMMENT '总价',
  `paypal`              DECIMAL(10,2) NOT NULL COMMENT '支付金额',
  `description`         VARCHAR(256) NOT NULL DEFAULT '' COMMENT '说明'
) ENGINE = innodb;

# 订单的商品项目
CREATE TABLE `order_item` (
  `id`                  INT NOT NULL AUTO_INCREMENT PRIMARY KEY COMMENT '主键',
  `order`               INT NOT NULL COMMENT '订单编号',
  `goods`               INT NOT NULL COMMENT '商品编号',
  `price`               DECIMAL(10,2) NOT NULL COMMENT '单价',
  `amount`              INT NOT NULL COMMENT '数量',
  `unit`                VARCHAR(8) NOT NULL DEFAULT '' COMMENT '单位'
) ENGINE  = innodb;


# 附加外键引用
ALTER TABLE `order` ADD FOREIGN KEY (`user`) REFERENCES ucenter_user (id);
ALTER TABLE `order_item` ADD FOREIGN KEY (`order`) REFERENCES `order` (id);