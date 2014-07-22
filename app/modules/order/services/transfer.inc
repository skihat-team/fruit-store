<?php

class Transfer {
    public static function submit(Order $order, $items, $uid) {
        Skihat::import('kernels.transactions.transaction', SKIHAT_PATH_LIBRARY);
        Skihat::import('goods.models.goods', SKIHAT_PATH_APP_MODULES);
        Skihat::import('order.models.order', SKIHAT_PATH_APP_MODULES);
        Skihat::import('order.models.order_item', SKIHAT_PATH_APP_MODULES);

        $goodsAll = Goods::fetchAll(array('Goods.id' => array_keys($items), 'Goods.sale' => Goods::SALE))->fetchObjects();
        if (empty($goodsAll)) return false;

        $totalAll = 0;
        foreach ($goodsAll as $goods) {
            $totalAll += ($goods->price * $items[$goods->id]['amount']);
        }

        $order->changeProps(array('status' => Order::ORDER_STATUS_NEW,
            'total' => $totalAll, 'shopping_date' => 0, 'user' => intval($uid),
            'paypal' => $totalAll, 'consignee_date' => 0
        ));

        try {
            Transaction::begin();

            #  如果保存订单失败。
            if (!$order->save()) return false;

            $itemsAll = array();
            foreach ($goodsAll as $goods) {
                # 如果商品数量大于1。
                if ($items[$goods->id]['amount']) {
                    array_push($itemsAll, array($order->key(), $goods->id, $goods->price, $items[$goods->id]['amount'], $goods->unit));
                }
            }

            # 返回值。
            $result = array(OrderItem::createMultiple(array('order', 'goods', 'price', 'amount', 'unit'), $itemsAll), $totalAll);
            Transaction::commit();

            return $result;
        } catch (Exception $ex) {
            Transaction::rollback();
        }
    }
}