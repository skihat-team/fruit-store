<?php

class OrderItem extends ApplicationModel {
    public static function config() {
        return array(
            self::META_LINKS => array(
                'Goods' => array(
                    self::META_LINKS_TYPE => self::BELONGS_TO,
                    self::META_LINKS_CLASS => 'goods.models.goods',
                    self::META_LINKS_FOREIGN => 'goods'
                )
            )
        );
    }
}