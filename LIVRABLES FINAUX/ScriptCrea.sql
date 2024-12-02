CREATE DATABASE IF NOT EXISTS `concurrence`;

USE `concurrence`;

DROP TABLE IF EXISTS `type`;
CREATE TABLE type(
                     id INT NOT NULL AUTO_INCREMENT,
                     name VARCHAR(50) NOT NULL,
                     wash_time INT NOT NULL,
                     PRIMARY KEY(id)
)

DROP TABLE IF EXISTS `utensils`;
CREATE TABLE utensils(
                         id INT NOT NULL AUTO_INCREMENT ,
                         name VARCHAR(100) NOT NULL,
                         quantity INT NOT NULL,
                         type_id INT NOT NULL,
                         PRIMARY KEY(id),
                         FOREIGN KEY(type_id) REFERENCES type(id)
)

DROP TABLE IF EXISTS `location`;
CREATE TABLE location(
                         id INT NOT NULL AUTO_INCREMENT,
                         name VARCHAR(50) NOT NULL,
                         validity INT NOT NULL,
                         PRIMARY KEY(id)
)

DROP TABLE IF EXISTS `products`;
CREATE TABLE products(
                         id INT NOT NULL AUTO_INCREMENT,
                         name VARCHAR(50) NOT NULL,
                         quantity INT NOT NULL,
                         drop_date DATE NOT NULL,
                         location_id INT NOT NULL,
                         PRIMARY KEY(id),
                         FOREIGN KEY(location_id) REFERENCES location(id)
)