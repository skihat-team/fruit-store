<?php

class CategoryController extends AdminController {
    public function indexAction() {
        $this['categories'] = GoodsCategory::fetchAll();
    }

    public function newAction() {
        if ($this->isPost()) {
            $this['category'] = new GoodsCategory($this->form('category'));

            if ($this['category']->save()) {
                $this->message('创建新的分类信息成功.', SKIHAT_MESSAGE_SUCCESS);
                $this->redirect('index');
            } else {
                $this->message('创建分类失败，请检查字段属性。', SKIHAT_MESSAGE_FAIL);
            }
        }
    }

    public function editAction() {
        if ($this->isPost()) {
            $this['category'] = new GoodsCategory($this->form('category'), true, true);
            if ($this['category']->save()) {
                $this->message('更新分类信息成功.', SKIHAT_MESSAGE_SUCCESS);
                $this->redirect('index');
            } else {
                $this->message('更新分类信息失败，请检查更新字段.', SKIHAT_MESSAGE_FAIL);
            }
        } else {
            $this['category'] = GoodsCategory::fetch($this->query('id'));

            if (empty($this['category'])) {
                $this->message('需要更新的分类信息不存在，请检查后重试.');
                $this->redirect('index');
            }
        }
    }

    public function deleteAction() {
        # 如果当前请求为POST，并且指定有ID参数。
        if ($this->isPost() && $id = $this->form('id')) {
            if (GoodsCategory::deleteAll(intval($id))) {
                $this->message('删除商品分类信息成功.', SKIHAT_MESSAGE_SUCCESS);
            }
        }

        $this->redirect('index');
    }

    public function actionModels() {
        Skihat::import('goods.models.goods_category', SKIHAT_PATH_APP_MODULES);
    }
}