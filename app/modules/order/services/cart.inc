<?php

class Cart {
    const CART_KEY = 'cart';

    const ID = 'id';
    const NAME = 'name';
    const THUMB = 'thumb';
    const PRICE = 'price';
    const UNIT = 'unit';
    const AMOUNT = 'amount';
    const DESCRIPTION = 'description';

    public static function add($goods, $amount) {
        # 如果商品编号或数据不正确，直接返回false。
        if (!$goods || !$amount) return false;

        # 如果当前还没有购物车SESSION信息。
        if (!isset($_SESSION[self::CART_KEY])) {
            $_SESSION[self::CART_KEY] = array();
        }

        # 如果当前商品已在购物车中。
        if ($_SESSION[self::CART_KEY][$goods]) {
            $_SESSION[self::CART_KEY][$goods][self::AMOUNT] += intval($amount);

            return true;
        } else {
            Skihat::import('goods.models.goods', SKIHAT_PATH_APP_MODULES);
            # 获取商品信息，如果商品正在销售，则加入购特车
            if ($goods = Goods::fetch(array('id' => intval($goods), 'sale' => Goods::SALE), array(), Model::FETCH_STYLE_OBJ)) {
                # 将商品信息增加到购物车。
                $_SESSION[self::CART_KEY][$goods->id] = array(
                    self::ID => $goods->id, self::NAME => $goods->name, self::THUMB => $goods->thumb, self::AMOUNT => intval($amount),
                    self::PRICE => $goods->price, self::UNIT => $goods->unit, self::DESCRIPTION => $goods->description
                );

                return true;
            }
        }

        return false;
    }

    public static function remove($goods) {
        if (isset($_SESSION[self::CART_KEY])) {
            unset($_SESSION[self::CART_KEY][$goods]);
        }
    }

    public static function change($goods, $amount) {
        # 如果商品或商品数量不正确直接返回。
        if (!$goods || !$amount) return;

        if (isset($_SESSION[self::CART_KEY]) && isset($_SESSION[self::CART_KEY][$goods])) {
            $_SESSION[self::CART_KEY][$goods][self::AMOUNT] = intval($amount);
        }
    }

    public static function update() {
        # 如果没有购物信息，直接返回。
        if (empty($_SESSION[self::CART_KEY])) return;

        Skihat::import('goods.models.goods', SKIHAT_PATH_APP_MODULES);
        $goodsAll = Goods::fetchAll(array('Goods.id' => array_keys($_SESSION[self::CART_KEY]),
            'Goods.sale' => Goods::SALE))->fetchList('id,price');

        foreach ($goodsAll as $goods => $price) {
            $amount = intval($_SESSION[self::CART_KEY][$goods][self::AMOUNT]);
            if (!empty($amount)) {
                $_SESSION[self::CART_KEY][$goods][self::PRICE] = $price;
            } else {
                unset($_SESSION[self::CART_KEY][$goods]);
            }
        }
    }

    public static function total() {
        $total = 0;

        foreach (self::items() as $item) {
            $total += ($item[self::PRICE] * $item[self::AMOUNT]);
        }

        return $total;
    }

    public static function clear() {
        unset($_SESSION[self::CART_KEY]);
    }

    public static function amounts() {
        return isset($_SESSION[self::CART_KEY]) ? count($_SESSION[self::CART_KEY]) : 0;
    }

    public static function items() {
        return array_key_value($_SESSION, self::CART_KEY, array());
    }
}