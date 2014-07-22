<?php

class Goods extends ApplicationModel {
    const CANCEL = 0;
    const OFFER = 1;
    const SALE = 1;
    const HOME = 1;

    public static function config() {
        return array(
            self::META_LINKS => array(
                'Category' => array(
                    self::META_LINKS_CLASS => 'goods.models.goods_category',
                    self::META_LINKS_TYPE => self::BELONGS_TO,
                    self::META_LINKS_FOREIGN => 'category'
                ),
                'Detail' => array(
                    self::META_LINKS_CLASS => 'goods.models.goods_detail',
                    self::META_LINKS_TYPE => self::HAS_ONE,
                    self::META_LINKS_FOREIGN => 'goods'
                )
            ),
            self::META_RULE => array(
                self::CREATE_RULES => array(
                    'name' => array('required' => true, 'strlen' => array(2 - 16)),
                    'thumb' => array('required' => true),
                    'price' => array('required' => true, 'numeric' => true, 'nummin' => 0),
                    'unit' => array('required' => true),
                    'description' => array('required' => true)
                ),
                self::UPDATE_RULES => array(
                    'name' => array('required' => true, 'strlen' => array(2 - 16)),
                    'thumb' => array('required' => true),
                    'price' => array('required' => true, 'numeric' => true, 'nummin' => 0),
                    'unit' => array('required' => true),
                    'description' => array('required' => true)
                )
            ),
            self::META_RULE_MESSAGE => array(
                'name' => array('required' => '商品名称不能为空.', 'strlen' => '商品名称必须是2-16个字符'),
                'thumb' => '缩略图不能为空.',
                'price' => array('required' => '价格不能为空.', 'numeric' => '价格必须是数字.', 'nummin' => '价格必须大于0.'),
                'unit' => '商品单位不能为空.',
                'description' => '商品简介信息不能为空.'
            )
        );
    }

    public static function homeAll($conditions) {
        return self::updateAll('home = 1', $conditions);
    }

    public static function cancelHomeAll($conditions) {
        return self::updateAll('home = 0', $conditions);
    }

    public static function offerAll($conditions) {
        return self::updateAll('offer = 1', $conditions);
    }

    public static function cancelOfferAll($conditions) {
        return self::updateAll('offer = 0', $conditions);
    }

    public static function saleAll($conditions) {
        return self::updateAll('sale = 1', $conditions);
    }

    public static function cancelSaleAll($conditions) {
        return self::updateAll('sale = 0', $conditions);
    }

    public static function fetchHomeAll() {
        return self::fetchAll('Goods.home = 1 AND Goods.sale = 1');
    }

    public static function fetchOfferAll() {
        return self::fetchAll('Goods.offer = 1 AND Goods.sale = 1');
    }

    public static function fetchSale($id, $syntax = array()) {
        if ($goods = self::fetch(array('Goods.id' => intval($id), 'Goods.sale' => self::SALE), $syntax)) {
            return $goods;
        }

        return false;
    }

    protected function _updateBefore(array &$syntax) {
        # 如果当前的缩略图为空，表示不更新。
        if (empty($this->_currentProps['thumb'])) {
            unset($this->_currentProps['thumb']);
        }

        return true;
    }
}