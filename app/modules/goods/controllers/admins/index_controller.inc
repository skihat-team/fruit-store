<?php
# 导入媒体资源管理对象。
Skihat::import('kernels.medias.media', SKIHAT_PATH_LIBRARY);

/**
 * 活动管理界面。
 */
class IndexController extends AdminController {
    public function indexAction() {
        $conditions = array();
        if ($title = $this->query('q')) {
            if (is_numeric($title)) {
                $conditions['Goods.id'] = intval($title);
            } else {
                $conditions['Goods.name like'] = '%' . addslashes($title) . '%';
            }
        }

        if ($cat = $this->query('cat')) {
            $conditions['Goods.category'] = intval($cat);
        }

        $this['goodsAll'] = Goods::fetchAll($conditions);
        $this['cats'] = GoodsCategory::fetchAll();
    }

    public function searchAction() {
        $this->redirect(array('q' => $this->form('q'), 'action' => 'index'));
    }

    public function newAction() {
        if ($this->isPost()) {
            $this['goodsDetail'] = new GoodsDetail($this->form('goodsDetail'));
            $this['goods'] = new Goods($this->form('goods'));
            $thumb = $this->file('goods');

            if (!empty($thumb)) {
                $this['goods']['thumb'] = Media::upload($thumb['thumb'], 'goods');
            }

            if ($this['goods']->save()) {
                $this['goodsDetail']->goods = $this['goods']->key();
                $this['goodsDetail']->save();

                $this->message('增加商品成功。', SKIHAT_MESSAGE_SUCCESS);
                $this->redirect('index');
                return;
            } else {
                $this->message('增加商品失败，请检查商品字段值.', SKIHAT_MESSAGE_FAIL);
            }
        }

        $this['cats'] = GoodsCategory::fetchAll();
    }

    public function  editAction() {
        if ($this->isPost()) {
            $thumb = $this->file('goods');
            $this['goods'] = new Goods($this->form('goods'), true, true);
            $this['goodsDetail'] = new GoodsDetail($this->form('goodsDetail'), true);

            if (!empty($thumb)) {
                $this['goods']['thumb'] = Media::upload($thumb['thumb'], 'goods');
            }

            if ($this['goods']->save()) {
                # 保存详细内容，注意指定goods条件，防止错误更新。
                $this['goodsDetail']->save(array(Model::SYNTAX_WHERE => array('goods' => $this['goods']->key())));
                $this->message('更新商品信息成功。', SKIHAT_MESSAGE_SUCCESS);
                $this->redirect('index', true);
                return;
            } else {
                $this->message('更新商品信息失败，请检查商品字段值。', SKIHAT_MESSAGE_FAIL);
            }
        } else {
            $id = $this->query('id');
            $this['goods'] = Goods::fetch(intval($id));
            $this['goodsDetail'] = GoodsDetail::fetch(array('goods' => intval($id)));

            if (empty($this['goods'])) {
                $this->message('对不起，更新的商品信息不存在.');
                $this->redirect('index', true);
                return;
            }
        }

        $this['cats'] = GoodsCategory::fetchAll();
    }

    public function deleteAction() {
        # 如果当前请求为POST并且包含id值。
        if ($this->isPost() && $id = $this->form('id')) {
            if ($rows = Goods::deleteAll(array('Goods.id' => $this->_idFilters($id)), array(Model::META_LINKS => 'Detail'))) {
                $this->message('删除商品成功，共删除' . $rows . '个商品信息.', SKIHAT_MESSAGE_SUCCESS);
            }
        }

        $this->redirect('index', true);
    }

    public function homeAction() {
        # 如果当前请求为POST并且包含id值。
        if ($this->isPost() && $id = $this->form('id')) {
            if ($rows = Goods::homeAll(array('id' => $this->_idFilters($id)))) {
                $this->message('设置首页商品成功，共设置' . $rows . '个商品信息.', SKIHAT_MESSAGE_SUCCESS);
            }
        }

        $this->redirect('index', true);
    }

    public function cancelHomeAction() {
        # 如果当前请求为POST并且包含id值。
        if ($this->isPost() && $id = $this->form('id')) {
            if ($rows = Goods::cancelHomeAll(array('id' => $this->_idFilters($id)))) {
                $this->message('取消首页商品成功，共取消了' . $rows . '个商品信息.', SKIHAT_MESSAGE_SUCCESS);
            }
        }

        $this->redirect('index', true);
    }

    public function offerAction() {
        # 如果当前请求为POST并且包含id值。
        if ($this->isPost() && $id = $this->form('id')) {
            if ($rows = Goods::offerAll(array('id' => $this->_idFilters($id)))) {
                $this->message('设置推荐商品成功，共取消了' . $rows . '个商品信息.', SKIHAT_MESSAGE_SUCCESS);
            }
        }

        $this->redirect('index', true);
    }

    public function cancelOfferAction() {
        # 如果当前请求为POST并且包含id值。
        if ($this->isPost() && $id = $this->form('id')) {
            if ($rows = Goods::cancelOfferAll(array('id' => $this->_idFilters($id)))) {
                $this->message('取消推荐商品成功，共取消了' . $rows . '个商品信息.', SKIHAT_MESSAGE_SUCCESS);
            }
        }

        $this->redirect('index', true);
    }

    public function saleAction() {
        # 如果当前请求为POST并且包含id值。
        if ($this->isPost() && $id = $this->form('id')) {
            if ($rows = Goods::saleAll(array('id' => $this->_idFilters($id)))) {
                $this->message('上架首页商品成功，共上架了' . $rows . '个商品信息.', SKIHAT_MESSAGE_SUCCESS);
            }
        }

        $this->redirect('index', true);
    }

    public function cancelSaleAction() {
        # 如果当前请求为POST并且包含id值。
        if ($this->isPost() && $id = $this->form('id')) {
            if ($rows = Goods::cancelSaleAll((array('id' => $this->_idFilters($id))))) {
                $this->message('下架首页商品成功，共下架了' . $rows . '个商品信息.', SKIHAT_MESSAGE_SUCCESS);
            }
        }

        $this->redirect('index', true);
    }

    public function actionFilters() {
        $filters = parent::actionFilters();
        $filters['paginate'] = array(
            SKIHAT_IOC_CLASS => 'controllers.filters.paginate_filter',
            SKIHAT_IOC_PATHS => SKIHAT_PATH_LIBRARY,
            'var' => 'goodsAll'
        );

        return $filters;
    }

    public function actionModels() {
        Skihat::import('goods.models.goods', SKIHAT_PATH_APP_MODULES);
        Skihat::import('goods.models.goods_detail', SKIHAT_PATH_APP_MODULES);
        Skihat::import('goods.models.goods_category', SKIHAT_PATH_APP_MODULES);
    }

    /**
     * @param $id
     *
     * @return array|int
     */
    protected function _idFilters($id) {
        if (!is_array($id)) return intval($id);
        return array_map('intval', $id);
    }
}