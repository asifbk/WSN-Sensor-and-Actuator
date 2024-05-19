/*
Navicat MySQL Data Transfer

Source Server         : Faryad
Source Server Version : 50505
Source Host           : localhost:3306
Source Database       : temperature

Target Server Type    : MYSQL
Target Server Version : 50505
File Encoding         : 65001

Date: 2017-12-25 12:16:40
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `devices_status`
-- ----------------------------
DROP TABLE IF EXISTS `devices_status`;
CREATE TABLE `devices_status` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `device_name` varchar(50) DEFAULT NULL,
  `device_status` tinyint(1) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of devices_status
-- ----------------------------
INSERT INTO `devices_status` VALUES ('1', 'home_sensor', '1');

-- ----------------------------
-- Table structure for `temps`
-- ----------------------------
DROP TABLE IF EXISTS `temps`;
CREATE TABLE `temps` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `temp` int(11) NOT NULL,
  `humidity` int(11) DEFAULT NULL,
  `time` time DEFAULT NULL,
  `dated` date DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of temps
-- ----------------------------
