<?php

class IndexController extends AdminController {

    public function indexAction() {
        $conditions = array();
        if ($q = $this->query('q', '')) {
            if (filter_var($q, FILTER_VALIDATE_EMAIL)) {
                $conditions['email'] = addslashes($q);
            } else if (is_numeric($q)) {
                $conditions['id'] = intval($q);
            } else {
                $conditions['name LIKE '] = '%' . addslashes($q) . '%';
            }
        }

        $this['users'] = UcenterUser::fetchAll($conditions);
    }

    public function editAction() {
        if ($this->isPost()) {
            $this['user'] = new UcenterUser($this->form('user'), true, true);
            if ($this['user']->save()) {
                $this->message('更新会员信息成功', SKIHAT_MESSAGE_SUCCESS);
                $this->redirect('index', true);
                return;
            }
        } else {
            $this['user'] = UcenterUser::fetch(intval($this->query('id', 0)));
        }
    }

    public function searchAction() {
        $this->redirect(array(SKIHAT_PARAM_ACTION => 'index', 'q' => $this->form('q')));
    }

    public function deleteAction() {
        # 如果当前为POST请求，并且包含ID值。
        if ($this->isPost() && $id = $this->form('id')) {
            if ($rows = UcenterUser::deleteAll(array('id' => $this->_idFilters($id)))) {
                $this->message('删除会员信息成功，共删除' . $rows . '个会员.', SKIHAT_MESSAGE_SUCCESS);
            }
        }

        $this->redirect('index', true);
    }

    public function allowAction() {
        if ($this->isPost() && $id = $this->form('id')) {
            if ($rows = UcenterUser::allowAll(array('id' => $this->_idFilters($id)))) {
                $this->message('开启访问成功，共开启' . $rows . '个账户的访问.', SKIHAT_MESSAGE_SUCCESS);
            }
        }

        $this->redirect('index', true);
    }

    public function denyAction() {
        if ($this->isPost() && $id = $this->form('id')) {
            if ($rows = UcenterUser::denyAll(array('id' => $this->_idFilters($id)))) {
                $this->message('关闭访问成功，共开启' . $rows . '个账户的访问.', SKIHAT_MESSAGE_SUCCESS);
            }
        }

        $this->redirect('index', true);
    }

    protected function _idFilters($id) {
        if (is_array($id)) return array_map('intval', $id);
        else return intval($id);
    }

    public function actionFilters() {
        $filters = parent::actionFilters();
        $filters['paginate'] = array('var' => 'users',
            SKIHAT_IOC_CLASS => 'controllers.filters.paginate_filter',
            SKIHAT_IOC_PATHS => SKIHAT_PATH_LIBRARY
        );
        
        return $filters;
    }

    public function actionModels() {
        Skihat::import('ucenter.models.ucenter_user', SKIHAT_PATH_APP_MODULES);
    }
}