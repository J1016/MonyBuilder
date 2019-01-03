local exec = Executor.get();

-- ��ӡ����̨ log �ķ���
-- content��Ҫ��ӡ���ִ���Ϣ
-- return��nil
--
function mony_trace(content)

	exec:trace(content);

end

-- ��ղ�������Ϣ
--
function mony_clear_http_param_map()

	exec:clearHttpParamMap();

end

-- ��ȡ��ǰ���ں������ķ���
-- return���õ������ں�����
-- 
function mony_date_milli()

	return exec:dateMilli();

end

-- ���ýű��ķ���
-- name���ű�����
-- return��nil
--
function mony_invoke(name)

	exec:invoke(name);

end

-- ��ȡ�������е�Ψһ code ��Ϣ
-- return���õ��� code ��Ϣ
--
function mony_sericode()

	return exec:sericode();

end

-- ��ȡ�����е�һ��
-- arrays����������
-- index����������
-- return���õ���������Ŀ
--
function mony_array_get(arrays , index)

	return exec:arrayGet(arrays , index);

end

-- ��ȡ����ĳ���
-- arrays����������
-- return���õ������鳤��
--
function mony_array_length(arrays)

	return exec:arrayLength(arrays);

end

-- ������֤����Ϣ�Ĳ���
-- pic_path��ͼƬ·����Ϣ
-- again_script_path����������Ľű���Ϣ
-- check_script_path�������֤��Ľű���Ϣ
-- return���������֤����
--
function mony_input_vercode(pic_path , again_script_path , check_script_path)

	return exec:inputVercode(pic_path , again_script_path , check_script_path);

end

-- ��ȡ�ض��� mouse pwd ��Ϣ
-- mouse_pwd_t��ʱ����Ϣ
-- return���õ��� mouse pwd ��Ϣ
--
function mony_fixed_gain_mouse_pwd(mouse_pwd_t)

	return exec:fixedGainMousePwd(mouse_pwd_t);

end

-- ����ȫ�ֲ����ķ���
-- key������Ϣ
-- return���õ��ĳ־û�������Ϣ
--
function mony_load_durable_param(key)

	return exec:loadDurableParam(key);

end

-- ����ȫ�ֲ����ķ���
-- key������Ϣ
-- value��ֵ��Ϣ
--
function mony_save_durable_param(key , value)

	exec:saveDurableParam(key , value);

end

-- ��ȡȫ�ֲ����ķ���
-- key������Ϣ
-- return���õ���ֵ��Ϣ
--
function mony_get_global_param(key)

	return exec:getGlobalParam(key);

end

-- ����ȫ�ֲ����ķ���
-- key������Ϣ
-- value��ֵ��Ϣ
--
function mony_set_global_param(key , value)
	
	exec:setGlobalParam(key , value);

end

-- ��ȡȫ�ֲ����ķ���
-- key������Ϣ
-- return���õ���ֵ��Ϣ
--
function mony_get_global_param(key)

	return exec:getGlobalParam(key);

end

-- �������������ķ���
-- key:	����Ϣ
-- value��ֵ��Ϣ
--
function mony_set_http_param(key , value)

	exec:setHttpParam(key , value);

end

-- ��ȡ������������ķ���
-- key:	����Ϣ
-- return���õ��Ľ��
--
function mony_get_http_response(key)

	return exec:getHttpResponse(key);

end

-- ��ȡ�������һ�� key �µ����� response �ķ���
-- key:	����Ϣ
-- return���õ��Ľ��
--
function mony_get_http_response_merge(key)

	return exec:getHttpResponseMerge(key);

end

-- ��ȡ����ȫ����������ķ���
-- return���õ��Ľ��
--
function mony_get_http_response_total()

	return exec:getHttpResponseTotal();

end

-- ����һ�� GET ����ķ������õ����Ϊ�ļ�
-- url��������Ϣ
-- file���ļ�����
--
function mony_http_get_file(url , file)

	return exec:httpGetGainFile(url , file);

end

-- ����һ�� POST ����ķ������õ����Ϊ�ļ�
-- url��������Ϣ
-- predata��ǰ�� post ����
-- data: Ҫ post ������
-- file���ļ�����
--
function mony_http_post_file(url , predata , data , file)

	return exec:httpPostGainFile(url , predata , data , file);

end

-- ����һ�� GET ����ķ���
-- url��������Ϣ
-- log_file���ļ� log ���ļ���
-- return���õ��Ľ����Ϣ
--
function mony_http_get(url , log_file)

	return exec:httpGet(url , log_file);

end

-- ����һ�� OPTIONS ����ķ���
-- url��������Ϣ
-- log_file���ļ� log ���ļ���
-- return���õ��Ľ����Ϣ
--
function mony_http_options(url , log_file)

	return exec:httpOptions(url , log_file);

end

-- ����һ�� POST ����ķ���
-- url��������Ϣ
-- predata��ǰ�� post ����
-- data: Ҫ post ������
-- log_file���ļ� log ���ļ���
-- return���õ��Ľ����Ϣ
--
function mony_http_post(url , predata , data , log_file)

	return exec:httpPost(url , predata , data , log_file);

end

-- ����һ�� POST ����ķ���
-- url��������Ϣ
-- predata��ǰ�� post ����
-- data: Ҫ post ������
-- enddata������ post ����
-- log_file���ļ� log ���ļ���
-- return���õ��Ľ����Ϣ
--
function mony_http_post_ext(url , predata , data , enddata , log_file)

	return exec:httpPostExt(url , predata , data , enddata , log_file);

end

-- ����������ķ���
--
-- return���õ��������
--
function mony_math_random_double()

	return exec:mathRandomDouble();

end

-- ����������ķ���
--
-- return���õ��������
--
function mony_math_random_double_value()

	return exec:mathRandomDoubleValue();

end


-- ����������ķ���
--
-- return���õ��������
--
function mony_math_random_int(start , finish)

	return exec:mathRandomInt(start , finish);

end

-- ����������ķ���
--
-- return���õ��������
--
function mony_math_random_int_value(start , finish)

	return exec:mathRandomIntValue(start , finish);

end

-- ��������ִ��ķ���
--
-- return���õ�������ִ�
--
function mony_math_random_string(length)

	return exec:mathRandomString(length);

end

-- ����һ���ִ��Ƚϵķ���
-- source: Դ�ִ�
-- dest: Ŀ���ִ�
-- return: �õ��Ľ��
--
function mony_string_equals(source , dest)

	return exec:stringEquals(source , dest);

end

-- ����һ���ִ���ȡ�ķ���
-- source: Դ�ִ�
-- left: ����ִ�
-- right: �Ҳ��ִ�
-- return: �õ��Ľ�ȡ�ִ�
--
function mony_string_cut(source , left , right)

	return exec:stringCut(source , left , right);

end

-- ����һ���м��ķ���
-- source��Դ�ִ�
-- filter�������ִ����� ## �ָ�
-- return���õ���������
--
function mony_string_find_line(source , filter)

	return exec:stringFindLine(source , filter)

end

-- �����ַ����滻�ķ���
-- source��Դ�ִ�
-- target��Ŀ���ִ�
-- value���滻��ֵ
-- return���õ������ַ���
--
function mony_string_replace(source , target , value)

	return exec:stringReplace(source , target , value);

end

-- ����һ�� url �ַ�������ķ���
-- value���ַ�����Ϣ
-- return���õ����ַ���������Ϣ
--
function mony_string_url_encp1(value)

	return exec:stringUrlEncode(value , "" , false);

end

-- ����һ�� url �ַ�������ķ���
-- value���ַ�����Ϣ
-- encode������ı�������
-- return���õ����ַ���������Ϣ
--
function mony_string_url_encp2(value , encode)

	return exec:stringUrlEncode(value , encode , false);

end

-- ����һ�� url �ַ�������ķ���
-- value���ַ�����Ϣ
-- encode������ı�������
-- exactly���Ƿ�������� % ������Ϣ
-- return���õ����ַ���������Ϣ
--
function mony_string_url_encp3(value , encode , exactly)

	return exec:stringUrlEncode(value , encode , exactly);

end

-- ����һ�� url �ַ�������ķ���
-- value���ַ�����Ϣ
-- return���õ����ַ���������Ϣ
--
function mony_string_url_decp1(value)

	return exec:stringUrlDecode(value , "");

end

-- ����һ�� url �ַ�������ķ���
-- value���ַ�����Ϣ
-- encode������ı�������
-- return���õ����ַ���������Ϣ
--
function mony_string_url_decp2(value, encode)

	return exec:stringUrlDecode(value , encode);

end

-- ֻ��һ��·���ַ�����ȡ�ļ����ķ���
-- content���ַ���Դ
-- return���õ������ַ���
--
function mony_string_gain_file_name(content)

	return exec:stringGainFileName(content);

end

-- ����һ�� rect limit ����ķ���
--
function mony_rect_limit(width , height , pic_width , pic_height)

	return exec:rectLimit(width , height , pic_width , pic_height);

end

-- �ص���ҳ�ķ���
-- content��������Ϣ
--
function mony_homepage_callback(content)

	return exec:homepageCallback(content);

end

-- ִ��һ�� js �����ķ���
-- file��js �ļ���
-- func��������
-- return���õ��Ľ����Ϣ
--
function mony_run_js(file, func, ...)

	return exec:runJs(file, func, ...);

end

-- Ѱ�����ƥ��λ�õķ���
-- file��Դͼ��
-- func��ģ��ͼ��
-- return���õ������ƥ���
--
function mony_match_template(soucre_file, template_file)

	return exec:matchTemplate(soucre_file, template_file);

end

-- ǿ�Ƶ�ǰ�߳����� msecs ����
-- msecs������
--
function mony_sleep(msecs)

	return exec:sleep(msecs);

end










