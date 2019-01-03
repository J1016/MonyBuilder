/* 
 * f 是 token
 * a 是坐标点加密后的数据，例如："1rSxUvr8ipq7\A33"
 */
var f = "9f25a9030f954f85bcb1a90b150e203d";
var dragX = 4;
var clientY = 120;
var startY = 120;
var beginTime = 1541494282357;

function y(e, t) 
{	
	function n(e, t) 
	{
		return e.charCodeAt(Math.floor(t % e.length))
	}
	
	function i(e, t) 
	{
		return t.split("").map(
			function(t, i) 
			{
				return t.charCodeAt(0) ^ n(e, i);
			});
	}
	
	return t = i(e, t),
	_(t);
}

function b() 
{
	return ["i", "/", "x", "1", "X", "g", "U", "0", "z", "7", "k", "8", "N", "+", "l", "C", "p", "O", "n", "P", "r", "v", "6", "\\", "q", "u", "2", "G", "j", "9", "H", "R", "c", "w", "T", "Y", "Z", "4", "b", "f", "S", "J", "B", "h", "a", "W", "s", "t", "A", "e", "o", "M", "I", "E", "Q", "5", "m", "D", "d", "V", "F", "L", "K", "y"];
}

function g() 
{
	return "3";
}
	
function _(e) 
{	
	if (null == e || void 0 == e)
	{
		return null;
	}    
	
	if (0 == e.length)
	{
		return "";
	}

	var t = 3;
	//try 
	//{
		for (var n = [], i = 0; i < e.length; ) 
		{
			if (!(i + t <= e.length)) 
			{
				n.push(m(e, i, e.length - i));
				break;
            }
			
			n.push(m(e, i, t)),
			i += t;
        }
		
		return n.join("");
	//} 
	//catch (r) 
	//{
		//throw new Error("1010");
	//}
}

function m(e, t, n) 
{
	var i, r, o, u = b(), l = g(), f = [];
	
	if (1 == n)
	{
		i = e[t],
		r = 0,
		o = 0,
		f.push(u[i >>> 2 & 63]),
		f.push(u[(i << 4 & 48) + (r >>> 4 & 15)]),
		f.push(l),
		f.push(l);
	}
	else if (2 == n)
	{
		i = e[t],
		r = e[t + 1],
		o = 0,
		f.push(u[i >>> 2 & 63]),
		f.push(u[(i << 4 & 48) + (r >>> 4 & 15)]),
		f.push(u[(r << 2 & 60) + (o >>> 6 & 3)]),
		f.push(l);
	}
	else 
	{
		if (3 != n)
		{
			throw new Error("1010");
		}
			
		i = e[t],
		r = e[t + 1],
		o = e[t + 2],
		f.push(u[i >>> 2 & 63]),
		f.push(u[(i << 4 & 48) + (r >>> 4 & 15)]),
		f.push(u[(r << 2 & 60) + (o >>> 6 & 3)]),
		f.push(u[63 & o])
	}
	
	return f.join("");
}

y(f, [Math.round(dragX < 0 ? 0 : dragX), Math.round(clientY - startY), (new Date).getTime() - beginTime] + "");


