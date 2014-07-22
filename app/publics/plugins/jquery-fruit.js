/**
 * jquery.fruit.js fruit的特效处理代码。
 */

(function ($) {
    $.fruitFields = function ($chkBoxes, fieldName, fields) {
        // 如果未设置初始化字段值；
        if (fields == undefined || fields == 'undefined') {
            fields = {};
        }

        if ($chkBoxes.size() == 0) return {};

        var i = 0;
        $chkBoxes.each(function () {
            var key = fieldName + '[' + (i++) + ']';
            fields[key] = $(this).val();
        });

        return fields;
    };
})(window.jQuery);

(function ($) {
    /**
     * fruit post 提供使用post提交数据的方式。
     *
     * @param $element
     * @param options
     * @constructor
     */
    var FruitPost = function ($element, options) {
        this.$element = $element;
        this.options = options;
        this.options.target = this.options.target || this.$element.attr('href');
        var that = this;

        this.$element.on('click', function (e) {
            e.preventDefault();
            that.submit();
        });

        this.submit = function () {
            var fields = this.options.fields
                , target = this.options.target
                , remote = this.options.remote;

            if (!target) return;
            if (typeof fields == 'string') {
                if (fields.charAt(0) == '#') {
                    fields = $(fields).data('chkall').fields();
                } else {
                    fields = eval('(' + fields + ')');
                }
            }
            else if ($.isFunction(fields)) fields = fields();

            if ($.isEmptyObject(fields)) {
                this.options.fieldsNotify();
                return;
            }

            if (this.options.confirm && !this.options.confirmNotify(this.options.confirm)) return;

            if (remote) {
                $.post(target, fields, this.options.remoteNotify);
            } else {
                var $form = $('<form method="post" action="' + target + '"></form>');
                var inputs = '';

                $.each(fields, function (name, value) {
                    inputs += '<input name="' + name + '" value="' + value + '" type="hidden" />';
                });

                $form.hide().append(inputs).appendTo('body');
                $form.submit();
            }

            this.$element.trigger($.Event('complete'));
        }
    };

    $.fn.fruitPost = function (option) {
        return this.each(function () {
            var $this = $(this)
                , data = $this.data('post')
                , options = $.extend({}, $.fn.fruitPost.defaults, $this.data(), typeof option == 'object' && option);

            if (!data) $this.data('post', (data = new FruitPost($this, options)));
            if (typeof option == 'string') data[option]();
            else if (options.submit) data.submit();
        });
    };

    $.fn.fruitPost.defaults = {
        fields: {},
        submit: false,
        remote: false,
        confirm: '请确认是否继续执行操作',
        fieldsNotify: function () {
            alert('请选择需要操作的记录。');
        },
        confirmNotify: function (msg) {
            return confirm(msg);
        },
        remoteNotify: function (data) {
            if (typeof data == 'string') {
                data = eval('(' + data + ')');
            }
        }
    };

    $(document).ready(function () {
        $("[data-toggle='fruit-post']").fruitPost({});
    });

})(window.jQuery);

(function ($) {
    /**
     * fruit Check all 提供js全选服务。
     *
     * @param $element
     * @param options
     * @constructor
     */
    var FruitCheckAll = function ($element, options) {
        this.$checkBoxes = $(options.target).find(':checkbox');
        this.$element = $element;
        this.options = options;
        var that = this;

        if (options.clickTrigger) {
            $(options.target).find(options.clickTrigger).on('click', function (e) {
                // 如果事情的节点不是触发器节点，则直接返回。
                if (e.target.nodeName.toLowerCase() != options.clickTrigger.toLowerCase()) return;

                var $checkbox = $(this).parents('.click-trigger').find(':checkbox');
                if ($checkbox.size() > 0 && !$checkbox.attr('checked')) {
                    $checkbox.attr('checked', true);
                } else if ($checkbox.size() > 0) {
                    $checkbox.removeAttr('checked');
                }

                that.change();
            });
        }

        this.$element.on('click', function () {
            that[$(this).attr('checked') ? 'check' : 'uncheck']();
        });

        this.$checkBoxes.on('click', function () {
            that.change();
        });

        this.change = function () {
            var chkAll = true;
            var chkOne = false;
            that.$checkBoxes.each(function () {
                if (!($(this).attr('checked'))) {
                    chkAll = false;
                } else {
                    chkOne = true;
                }
            });

            that.$element.attr('checked', chkAll);

            if (chkAll) that.$element.trigger('chkall');
            else that.$element.trigger('unchkall');

            if (chkOne) that.$element.trigger('check');
            else that.$element.trigger('uncheck');

            // 处理选择目标元素
            if (that.options.check) {
                if (chkOne) $(that.options.check).show(400);
                else $(that.options.check).hide(400);
            }
        };

        this.check = function () {
            this.$element.attr('checked', 'checked');
            this.$checkBoxes.attr('checked', 'checked');

            this.change();
        };

        this.uncheck = function () {
            this.$element.removeAttr('checked');
            this.$checkBoxes.removeAttr('checked');

            this.change();
        };

        /**
         * 获取选择checkbox的字段值。
         */
        this.fields = function (fieldName, fields) {
            // 初始化选项。
            if (fieldName == undefined) fieldName = 'id';
            if (fields == undefined) fields = {};

            var idx = 0;
            this.$checkBoxes.each(function () {
                if ($(this).attr('checked')) {
                    fields[fieldName + '[' + (idx++) + ']'] = $(this).val();
                }
            });

            return fields;
        };
    };

    $.fn.fruitCheckAll = function (option) {
        return this.each(function () {
            var $this = $(this)
                , data = $this.data('chkall')
                , options = $.extend({}, $.fn.fruitCheckAll.defaults, $this.data(), typeof option == 'object' && option);

            if (!data) $this.data('chkall', (data = new FruitCheckAll($this, options)));
            if (typeof option == 'string') data[option]();
        });
    };

    $.fn.fruitCheckAll.defaults = {
        target: 'table tbody',
        check: false,
        clickTrigger: 'li'
    };

    $(document).ready(function () {
        $("[data-toggle='fruit-chkall']").fruitCheckAll({});
    });
})(jQuery);

/**
 * 防止重复提交。
 */
(function ($) {
    $(document).ready(function () {
        $("form").submit(function () {
            var btn = $(this).find("[type='submit']");
            btn.button('loading')
            setTimeout(function () {
                btn.button('reset')
            }, 3000)
        });
    });

})(jQuery);