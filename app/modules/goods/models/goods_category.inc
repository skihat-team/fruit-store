<?php

class GoodsCategory extends ApplicationModel {
    public static function config() {
        return array(
            self::META_LINKS => array(
                'GoodsAll' => array(
                    self::META_LINKS_CLASS => 'goods.models.goods',
                    self::META_LINKS_TYPE => self::HAS_MANY,
                    self::META_LINKS_FOREIGN => 'category'
                )
            ),
            self::META_RULE => array(
                self::CREATE_RULES => array(
                    'name' => 'required',
                    'pinyin' => 'required'
                ),
                self::UPDATE_RULES => array(
                    'name' => 'required',
                    'pinyin' => 'required'
                )
            ),
            self::META_RULE_MESSAGE => array(
                'name' => '分类名称不能为空.',
                'pinyin' => '拼音码不能为空.'
            )
        );
    }
}