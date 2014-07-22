<?php

class IndexController extends ApplicationController {

    public function indexAction() {
        if ($cat = $this->query('id')) {
            if ($category = GoodsCategory::fetch(intval($cat))) {
                $this['title'] = $category->name;
            } else {
                $this->error(404);
                return;
            }
            $this['goodsAll'] = Goods::fetchAll(array('Goods.category' => intval($cat), 'Goods.sale' => 1));
        } else {
            $this['goodsAll'] = Goods::fetchAll(array('Goods.sale' => 1));
            $this['title'] = '全部水果';
        }
    }

    public function showAction() {
        $this['goods'] = Goods::fetchSale($this->query('id', 0), array(Model::META_LINKS => array('Category', 'Detail')));

        # 如果没有找到商品。
        if (empty($this['goods'])) {
            $this->error(404);
        }
    }

    public function searchAction() {

    }

    public function actionModels() {
        Skihat::import('goods.models.goods', SKIHAT_PATH_APP_MODULES);
        Skihat::import('goods.models.goods_category', SKIHAT_PATH_APP_MODULES);
    }

    public function actionFilters() {
        return array(
            'paginateFilter' => array('var' => 'goodsAll', 'size' => 6,
                SKIHAT_IOC_CLASS => 'controllers.filters.paginate_filter',
                SKIHAT_IOC_PATHS => SKIHAT_PATH_LIBRARY),
            'cacheFilter' => array(
                SKIHAT_IOC_PATHS => SKIHAT_PATH_LIBRARY,
                SKIHAT_IOC_CLASS => 'controllers.filters.cache_filter',
                'actionMethods' => array('indexAction', 'showAction')
            ));
    }
}