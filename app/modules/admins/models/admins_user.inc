<?php

/**
 * 系统管理员模型，提供系统管理员的业务和数据处理。
 */
class AdminsUser extends ApplicationModel {

    const ACCESS_ALLOW = 1;
    const ACCESS_DENY = 0;

    public static function config() {
        return array(
            self::META_READONLY => array(
                'created',
                'login_count',
                'login_lasted_date',
                'login_lasted_address'
            ),
            self::META_RULE => array(
                self::CREATE_RULES => array(
                    'name' => array('required' => true, 'strmin' => 2, 'strmax' => 15),
                    'password' => array('required' => true, 'strmin' => 6, 'strmax' => 16)
                ),
                self::UPDATE_RULES => array(
                    'name' => array('required' => true, 'strmin' => 2, 'strmax' => 15),
                    'password' => array('strmin' => 6, 'strmax' => 16)
                )
            ),
            self::META_RULE_MESSAGE => array(
                'name' => '用户名不能为空，并且要求2-15个字符',
                'password' => array('required' => '密码不能为空', 'strmin' => '为了保存安全，密码长度必须为6-16个字符', 'strmax' => '为了保存安全，密码长度必须为6-16个字符')
            )
        );
    }

    public static function authenticate($user, $pass) {
        # 从数据库中检索数据。
        if ($user = self::fetch(array('AdminsUser.name' => $user, 'AdminsUser.password' => $pass,
            'AdminsUser.allow_access' => self::ACCESS_ALLOW), array(), self::FETCH_STYLE_OBJ)
        ) {
            # 更新最后登录时间和登录地址。
            self::updateAll(array('AdminsUser.login_count' => $user->login_count + 1,
                'AdminsUser.login_lasted_date' => time(), 'AdminsUser.login_lasted_address' => client_address()
            ), $user->id);

            return $user;
        }

        return false;
    }

    public static function allowAll($conditions, $syntax = array()) {
        if (is_array($conditions)) {
            $conditions['AdminsUser.allow_access'] = self::ACCESS_DENY;
        }

        return self::updateAll(array('AdminsUser.allow_access' => self::ACCESS_ALLOW), $conditions, $syntax);
    }

    public static function denyAll($conditions, $syntax = array()) {
        if (is_array($conditions)) {
            $conditions['AdminsUser.allow_access'] = self::ACCESS_ALLOW;
        }

        return self::updateAll(array('AdminsUser.allow_access' => self::ACCESS_DENY), $conditions, $syntax);
    }

    protected function _updateBefore(array &$syntax) {
        # 如果没有指定密码，则去除密码的内容。
        if (empty($this->_currentProps['password'])) {
            unset($this->_currentProps['password']);
        }

        return true;
    }

    protected function _createBefore(array &$syntax) {
        $this->_currentProps['login_count'] = 0;
        $this->_currentProps['login_lasted_date'] = 0;
        $this->_currentProps['login_lasted_address'] = '';

        return true;
    }
}