<?php

class UserController extends AdminController {
    public function indexAction() {
        $this['users'] = AdminsUser::fetchAll();
    }

    public function newAction() {
        if ($this->isPost()) {
            $this['user'] = new AdminsUser($this->form('user'));

            if ($this['user']->save()) {
                $this->message('创建管理员信息成功', SKIHAT_MESSAGE_SUCCESS);
                $this->redirect('index');
                return;
            } else {
                $this->message('创建管理员失败，请检查字段值', SKIHAT_MESSAGE_FAIL);
            }
        }
    }

    public function editAction() {
        if ($this->isPost()) {
            $this['user'] = new AdminsUser($this->form('user'), true, true);

            if ($this['user']->save()) {
                $this->message('更新管理员信息成功', SKIHAT_MESSAGE_SUCCESS);
                $this->redirect('index', true);
            } else {
                $this->message('更新管理员信息失败，请检查字段值', SKIHAT_MESSAGE_FAIL);
            }
        } else {
            $this['user'] = AdminsUser::fetch($this->query('id'));

            if (empty($this['user'])) {
                $this->message('对不起，指定的管理员信息不存在。', SKIHAT_MESSAGE_INFO);
                $this->redirect('index', true);
            }
        }
    }

    public function deleteAction() {
        if ($this->isPost() && $id = $this->form('id')) {
            if (AdminsUser::deleteAll(intval($id))) {
                $this->message('删除管理员信息成功。', SKIHAT_MESSAGE_SUCCESS);
            }
        }

        $this->redirect('index', true);
    }

    public function allowAction() {
        if ($this->isPost() && $id = $this->form('id')) {
            if ($rows = AdminsUser::allowAll(array('id' => $this->_idFilter($id)))) {
                $this->message("启用管理账户成功，共启用了{$rows}个账户对系统的访问。", SKIHAT_MESSAGE_SUCCESS);
            }
        }

        $this->redirect('index', true);
    }

    public function denyAction() {
        if ($this->isPost() && $id = $this->form('id')) {
            if ($rows = AdminsUser::denyAll(array('id' => $this->_idFilter($id)))) {
                $this->message("禁用管理账户成功，共禁止了{$rows}个账户对系统的访问。", SKIHAT_MESSAGE_SUCCESS);
            }
        }

        $this->redirect('index', true);
    }

    /**
     * 导入活动模型。
     */
    public function actionModels() {
        Skihat::import('admins.models.admins_user', SKIHAT_PATH_APP_MODULES);
    }

    /**
     * 生成活动过滤器。
     *
     * @return array|void
     */
    public function actionFilters() {
        $filters = parent::actionFilters();
        $filters['paginate'] = array(
            SKIHAT_IOC_CLASS => 'controllers.filters.paginate_filter',
            SKIHAT_IOC_PATHS => SKIHAT_PATH_LIBRARY, 'var' => 'users'
        );

        return $filters;
    }

    protected function _idFilter($id) {
        if (is_array($id)) return array_map('intval', $id);
        return intval($id);
    }
}