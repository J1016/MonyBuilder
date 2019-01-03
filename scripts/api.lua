local exec = Executor.get();

-- 打印控制台 log 的方法
-- content：要打印的字串信息
-- return：nil
--
function mony_trace(content)

	exec:trace(content);

end

-- 清空参数表信息
--
function mony_clear_http_param_map()

	exec:clearHttpParamMap();

end

-- 获取当前日期毫秒数的方法
-- return：得到的日期毫秒数
-- 
function mony_date_milli()

	return exec:dateMilli();

end

-- 调用脚本的方法
-- name：脚本名称
-- return：nil
--
function mony_invoke(name)

	exec:invoke(name);

end

-- 获取本次运行的唯一 code 信息
-- return：得到的 code 信息
--
function mony_sericode()

	return exec:sericode();

end

-- 获取数组中的一项
-- arrays：数组内容
-- index：数组索引
-- return：得到的数组条目
--
function mony_array_get(arrays , index)

	return exec:arrayGet(arrays , index);

end

-- 获取数组的长度
-- arrays：数组内容
-- return：得到的数组长度
--
function mony_array_length(arrays)

	return exec:arrayLength(arrays);

end

-- 输入验证码信息的操作
-- pic_path：图片路径信息
-- again_script_path：重新输入的脚本信息
-- check_script_path：检查验证码的脚本信息
-- return：输入的验证码结果
--
function mony_input_vercode(pic_path , again_script_path , check_script_path)

	return exec:inputVercode(pic_path , again_script_path , check_script_path);

end

-- 获取特定的 mouse pwd 信息
-- mouse_pwd_t：时间信息
-- return：得到的 mouse pwd 信息
--
function mony_fixed_gain_mouse_pwd(mouse_pwd_t)

	return exec:fixedGainMousePwd(mouse_pwd_t);

end

-- 载入全局参数的方法
-- key：键信息
-- return：得到的持久化参数信息
--
function mony_load_durable_param(key)

	return exec:loadDurableParam(key);

end

-- 保存全局参数的方法
-- key：键信息
-- value：值信息
--
function mony_save_durable_param(key , value)

	exec:saveDurableParam(key , value);

end

-- 获取全局参数的方法
-- key：键信息
-- return：得到的值信息
--
function mony_get_global_param(key)

	return exec:getGlobalParam(key);

end

-- 设置全局参数的方法
-- key：键信息
-- value：值信息
--
function mony_set_global_param(key , value)
	
	exec:setGlobalParam(key , value);

end

-- 获取全局参数的方法
-- key：键信息
-- return：得到的值信息
--
function mony_get_global_param(key)

	return exec:getGlobalParam(key);

end

-- 设置联网参数的方法
-- key:	键信息
-- value：值信息
--
function mony_set_http_param(key , value)

	exec:setHttpParam(key , value);

end

-- 获取联网结果参数的方法
-- key:	键信息
-- return：得到的结果
--
function mony_get_http_response(key)

	return exec:getHttpResponse(key);

end

-- 获取联网结果一个 key 下的所有 response 的方法
-- key:	键信息
-- return：得到的结果
--
function mony_get_http_response_merge(key)

	return exec:getHttpResponseMerge(key);

end

-- 获取联网全部结果参数的方法
-- return：得到的结果
--
function mony_get_http_response_total()

	return exec:getHttpResponseTotal();

end

-- 进行一次 GET 请求的方法，得到结果为文件
-- url：链接信息
-- file：文件名称
--
function mony_http_get_file(url , file)

	return exec:httpGetGainFile(url , file);

end

-- 进行一次 POST 请求的方法，得到结果为文件
-- url：链接信息
-- predata：前置 post 数据
-- data: 要 post 的数据
-- file：文件名称
--
function mony_http_post_file(url , predata , data , file)

	return exec:httpPostGainFile(url , predata , data , file);

end

-- 进行一次 GET 请求的方法
-- url：链接信息
-- log_file：文件 log 的文件名
-- return：得到的结果信息
--
function mony_http_get(url , log_file)

	return exec:httpGet(url , log_file);

end

-- 进行一次 OPTIONS 请求的方法
-- url：链接信息
-- log_file：文件 log 的文件名
-- return：得到的结果信息
--
function mony_http_options(url , log_file)

	return exec:httpOptions(url , log_file);

end

-- 进行一次 POST 请求的方法
-- url：链接信息
-- predata：前置 post 数据
-- data: 要 post 的数据
-- log_file：文件 log 的文件名
-- return：得到的结果信息
--
function mony_http_post(url , predata , data , log_file)

	return exec:httpPost(url , predata , data , log_file);

end

-- 进行一次 POST 请求的方法
-- url：链接信息
-- predata：前置 post 数据
-- data: 要 post 的数据
-- enddata：后置 post 数据
-- log_file：文件 log 的文件名
-- return：得到的结果信息
--
function mony_http_post_ext(url , predata , data , enddata , log_file)

	return exec:httpPostExt(url , predata , data , enddata , log_file);

end

-- 生成随机数的方法
--
-- return：得到的随机数
--
function mony_math_random_double()

	return exec:mathRandomDouble();

end

-- 生成随机数的方法
--
-- return：得到的随机数
--
function mony_math_random_double_value()

	return exec:mathRandomDoubleValue();

end


-- 生成随机数的方法
--
-- return：得到的随机数
--
function mony_math_random_int(start , finish)

	return exec:mathRandomInt(start , finish);

end

-- 生成随机数的方法
--
-- return：得到的随机数
--
function mony_math_random_int_value(start , finish)

	return exec:mathRandomIntValue(start , finish);

end

-- 生成随机字串的方法
--
-- return：得到的随机字串
--
function mony_math_random_string(length)

	return exec:mathRandomString(length);

end

-- 进行一次字串比较的方法
-- source: 源字串
-- dest: 目标字串
-- return: 得到的结果
--
function mony_string_equals(source , dest)

	return exec:stringEquals(source , dest);

end

-- 进行一次字串截取的方法
-- source: 源字串
-- left: 左侧字串
-- right: 右侧字串
-- return: 得到的截取字串
--
function mony_string_cut(source , left , right)

	return exec:stringCut(source , left , right);

end

-- 查找一个行集的方法
-- source：源字串
-- filter：过滤字串，以 ## 分隔
-- return：得到的行数组
--
function mony_string_find_line(source , filter)

	return exec:stringFindLine(source , filter)

end

-- 进行字符串替换的方法
-- source：源字串
-- target：目标字串
-- value：替换的值
-- return：得到的新字符串
--
function mony_string_replace(source , target , value)

	return exec:stringReplace(source , target , value);

end

-- 进行一次 url 字符串编码的方法
-- value：字符串信息
-- return：得到的字符串编码信息
--
function mony_string_url_encp1(value)

	return exec:stringUrlEncode(value , "" , false);

end

-- 进行一次 url 字符串编码的方法
-- value：字符串信息
-- encode：具体的编码类型
-- return：得到的字符串编码信息
--
function mony_string_url_encp2(value , encode)

	return exec:stringUrlEncode(value , encode , false);

end

-- 进行一次 url 字符串编码的方法
-- value：字符串信息
-- encode：具体的编码类型
-- exactly：是否编码类似 % 这种信息
-- return：得到的字符串编码信息
--
function mony_string_url_encp3(value , encode , exactly)

	return exec:stringUrlEncode(value , encode , exactly);

end

-- 进行一次 url 字符串解码的方法
-- value：字符串信息
-- return：得到的字符串解码信息
--
function mony_string_url_decp1(value)

	return exec:stringUrlDecode(value , "");

end

-- 进行一次 url 字符串解码的方法
-- value：字符串信息
-- encode：具体的编码类型
-- return：得到的字符串解码信息
--
function mony_string_url_decp2(value, encode)

	return exec:stringUrlDecode(value , encode);

end

-- 只将一个路径字符串留取文件名的方法
-- content：字符串源
-- return：得到的新字符串
--
function mony_string_gain_file_name(content)

	return exec:stringGainFileName(content);

end

-- 进行一次 rect limit 计算的方法
--
function mony_rect_limit(width , height , pic_width , pic_height)

	return exec:rectLimit(width , height , pic_width , pic_height);

end

-- 回调首页的方法
-- content：内容信息
--
function mony_homepage_callback(content)

	return exec:homepageCallback(content);

end

-- 执行一次 js 函数的方法
-- file：js 文件名
-- func：函数名
-- return：得到的结果信息
--
function mony_run_js(file, func, ...)

	return exec:runJs(file, func, ...);

end

-- 寻找最佳匹配位置的方法
-- file：源图像
-- func：模板图像
-- return：得到的最佳匹配点
--
function mony_match_template(soucre_file, template_file)

	return exec:matchTemplate(soucre_file, template_file);

end

-- 强制当前线程休眠 msecs 毫秒
-- msecs：毫秒
--
function mony_sleep(msecs)

	return exec:sleep(msecs);

end










