<?php

class Order extends ApplicationModel {
    # 订单状态
    const ORDER_STATUS_NEW = 1; # 新订单
    const ORDER_STATUS_SHOPPING = 2; # 正在配送
    const ORDER_STATUS_COMPLETE = 3; # 已完成
    const ORDER_STATUS_TRASH = 4; # 已删除

    public static function statusNames($status) {
        return array_key_value(self::$_statusNames, $status, '未知');
    }

    public static function trashAll($conditions) {
        if (is_array($conditions)) {
            $conditions['Order.status'] = self::ORDER_STATUS_NEW;
        }

        return self::updateAll('Order.status = 4', $conditions);
    }

    public static function shoppingAll($conditions) {
        if (is_array($conditions)) {
            $conditions['Order.status'] = self::ORDER_STATUS_NEW;
        }

        return self::updateAll('Order.status = 2', $conditions);
    }

    public static function completeAll($conditions) {
        if (is_array($conditions)) {
            $conditions['Order.status'] = self::ORDER_STATUS_SHOPPING;
        }

        return self::updateAll('Order.status = 3', $conditions);
    }

    public static function config() {
        return array(
            self::META_LINKS => array(
                'User' => array(
                    self::META_LINKS_TYPE => self::BELONGS_TO,
                    self::META_LINKS_CLASS => 'ucenter.models.ucenter_user',
                    self::META_LINKS_FOREIGN => 'user'
                ),
                'Items' => array(
                    self::META_LINKS_TYPE => self::HAS_MANY,
                    self::META_LINKS_CLASS => 'order.models.order_item',
                    self::META_LINKS_FOREIGN => 'OrderItem.order'
                )
            ),
            self::META_RULE => array(
                self::CREATE_RULES => array(
                    'telephone' => array('required' => true, 'telephone' => true),
                    'consignee' => 'required'
                )
            ),
            self::META_RULE_MESSAGE => array(
                'telephone' => array('required' => '联系电话不能为空.', 'telephone' => '电话格式不正确'),
                'consignee' => '联系人不能为空.'
            )
        );
    }

    protected static $_statusNames = array(
        self::ORDER_STATUS_NEW => '新订单',
        self::ORDER_STATUS_SHOPPING => '正在配送',
        self::ORDER_STATUS_TRASH => '已取消',
        self::ORDER_STATUS_COMPLETE => '已完成'
    );
}