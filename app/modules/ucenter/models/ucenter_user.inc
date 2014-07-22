<?php

class UcenterUser extends ApplicationModel {
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
                    'email' => array('email' => true, 'required' => true),
                    'password' => array('required' => true, 'strmin' => 6, 'strmax' => 16)
                ),
                self::UPDATE_RULES => array(
                    'name' => array('required' => true, 'strmin' => 2, 'strmax' => 15),
                    'email' => array('email' => true, 'required' => true),
                    'password' => array('strmin' => 6, 'strmax' => 16)
                )
            ),
            self::META_RULE_MESSAGE => array(
                'name' => array('required' => '用户名不能为空', 'strmin' => '用户名必须大于2个字符', 'strmax' => '用户名不能超过16个字符'),
                'email' => array('email' => '邮箱地址不正确', 'required' => '邮箱不能为空'),
                'password' => '密码不能为空，并且必须大于6个字符小于16个字符'
            ),
        );
    }

    public static function authenticate($email, $password) {
        if ($user = self::fetch(array('email' => $email, 'password' => $password, 'allow_access' => self::ACCESS_ALLOW), array(), self::FETCH_STYLE_OBJ)) {
            self::updateAll(array('login_count' => $user->login_count + 1, 'login_lasted_date' => time(), 'login_lasted_address' => client_address()), $user->id);
            return $user;
        }

        return false;
    }

    public static function password($id, $oldPassword, $newPassword) {
        return self::updateAll(array('password' => $newPassword), array(
            'id' => intval($id), 'password' => $oldPassword
        ));
    }

    public static function allowAll($conditions, $syntax = array()) {
        if (is_array($conditions)) {
            $conditions['UcenterUser.allow_access'] = self::ACCESS_DENY;
        }

        return self::updateAll(array('UcenterUser.allow_access' => self::ACCESS_ALLOW), $conditions, $syntax);
    }

    public static function denyAll($conditions, $syntax = array()) {
        if (is_array($conditions)) {
            $conditions['UcenterUser.allow_access'] = self::ACCESS_ALLOW;
        }

        return self::updateAll(array('UcenterUser.allow_access' => self::ACCESS_DENY), $conditions, $syntax);
    }

    protected function _updateBefore(array &$syntax) {
        # 如果没有指定密码，直接钭密码去除。
        if (empty($this->_currentProps['password'])) {
            unset($this->_currentProps['password']);
        }

        return true;
    }
}