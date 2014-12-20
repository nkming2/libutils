/*
 * js_html_log_strategy.tcc
 *
 * Author: Ming Tsang
 * Copyright (c) 2014 Ming Tsang
 * Refer to LICENSE for details
 */

#pragma once

#include <string>

#include "libutils/io/js_html_log_strategy.h"
#include "libutils/io/logger.h"

namespace utils
{
namespace io
{

template<typename CharT_>
std::string JsHtmlLogStrategy<CharT_>::OnAddHeader()
{
	return HtmlLogStrategy<CharT_>::OnAddHeader() +
			R"HEREDOC(
<style>
p.log:hover{background-color:#D3E8FF;}
fieldset{border:0;}
</style>
<script src='https://ajax.googleapis.com/ajax/libs/jquery/2.0.3/jquery.min.js'></script>
<script>
$(function()
{
	var array = ['fatal', 'error', 'warning', 'info', 'debug', 'verbose'];
	for (var i = 0; i < array.length; ++i)
	{
		var $switch = $('input#switch-' + array[i], 'div#filter-options');
		$switch.data('priority', array[i]);
		$switch.on('change', function()
				{
					var $select = $('p.' + $(this).data('priority'),
							'#log-content').css('display', 'block');
					if (this.checked)
					{
						$select.css('display', 'block');
					}
					else
					{
						$select.css('display', 'none');
					}
					return;
				});
	}
	return;
});
</script>
)HEREDOC";
}

template<typename CharT_>
std::string JsHtmlLogStrategy<CharT_>::OnAddPreBody()
{
	return R"HEREDOC(
<h2>Filter options</h2>
<div id='filter-options'>
Priority:
<fieldset>
<label for='switch-fatal'>Fatal</label>
<input type='checkbox' id='switch-fatal' checked='true' />
<label for='switch-error'>Error</label>
<input type='checkbox' id='switch-error' checked='true' />
<label for='switch-warning'>Warning</label>
<input type='checkbox' id='switch-warning' checked='true' />
<label for='switch-info'>Info</label>
<input type='checkbox' id='switch-info' checked='true' />
<label for='switch-debug'>Debug</label>
<input type='checkbox' id='switch-debug' checked='true' />
<label for='switch-verbose'>Verbose</label>
<input type='checkbox' id='switch-verbose' checked='true' />
</fieldset>
</div>
<h2>Logs</h2>
<div id='log-content'>
)HEREDOC";
}

}
}
