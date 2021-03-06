class Mq4ChartObjects
{
	private readonly ChartObjects _algoChartObjects;
	private readonly TimeSeries _timeSeries;

	private readonly Dictionary<string, Mq4Object> _mq4ObjectByName = new Dictionary<string, Mq4Object>();
	private readonly List<string> _mq4ObjectNameByIndex = new List<string>();

	public Mq4ChartObjects(ChartObjects chartObjects, TimeSeries timeSeries)
	{
		_algoChartObjects = chartObjects;
		_timeSeries = timeSeries;
	}

	[Conditional("ObjectsTotal")] 
	public int ObjectsTotal(int type)
	{
		switch (type)
		{
			[Conditional("OBJ_VLINE")] 
			//{
			case OBJ_VLINE:
				return _mq4ObjectByName.Values.OfType<Mq4VerticalLine>().Count();
			//}
			[Conditional("OBJ_HLINE")] 
			//{
			case OBJ_HLINE:
				return _mq4ObjectByName.Values.OfType<Mq4HorizontalLine>().Count();
			//}
			[Conditional("OBJ_TEXT")] 
			//{
			case OBJ_TEXT:
				return _mq4ObjectByName.Values.OfType<Mq4Text>().Count();                                     
			//}
			[Conditional("OBJ_LABEL")] 
			//{
			case OBJ_LABEL:
				return _mq4ObjectByName.Values.OfType<Mq4Label>().Count();                                     
			//}
			[Conditional("OBJ_TREND")] 
			//{
			case OBJ_TREND:
				return _mq4ObjectByName.Values.OfType<Mq4TrendLine>().Count();                                     
			//}
			[Conditional("OBJ_RECTANGLE")] 
			//{
			case OBJ_RECTANGLE:
				return _mq4ObjectByName.Values.OfType<Mq4Rectangle>().Count();                                     
			//}					
			[Conditional("OBJ_ARROW")] 
			//{
			case OBJ_ARROW:
				return _mq4ObjectByName.Values.OfType<Mq4Arrow>().Count();                                     
			//}			
			[Conditional("OBJ_FIBO")] 
			//{
			case OBJ_FIBO:
				return _mq4ObjectByName.Values.OfType<Mq4Fibo>().Count();                                     
			//}
			[Conditional("EMPTY")] 
			//{
			case EMPTY:
				return _mq4ObjectByName.Count;   
			//}
		}
		return 0;
	}

	[Conditional("ObjectCreate")] 
	public void Create(string name, int type, int window, int time1, double price1, int time2,
								double price2, int time3, double price3)
	{
		Mq4Object mq4Object = null;
		[Conditional("OBJ_VLINE", "OBJ_HLINE", "OBJ_TEXT", "OBJ_LABEL", "OBJ_TREND", "OBJ_RECTANGLE", "OBJ_ARROW", "OBJ_FIBO")] 
		switch (type)
		{
			[Conditional("OBJ_VLINE")] 
			//{
			case OBJ_VLINE:
				mq4Object = new Mq4VerticalLine(name, type, _algoChartObjects);
				break;   
			//}
			[Conditional("OBJ_HLINE")] 
			//{
			case OBJ_HLINE:
				mq4Object = new Mq4HorizontalLine(name, type, _algoChartObjects);
				break;                        
			//}
			[Conditional("OBJ_TEXT")] 
			//{
			case OBJ_TEXT:
				mq4Object = new Mq4Text(name, type, _algoChartObjects, _timeSeries);
				break;                                        
			//}
			[Conditional("OBJ_LABEL")] 
			//{
			case OBJ_LABEL:
				mq4Object = new Mq4Label(name, type, _algoChartObjects);
				break;
			//}
			[Conditional("OBJ_TREND")] 
			//{
			case OBJ_TREND:
				mq4Object = new Mq4TrendLine(name, type, _algoChartObjects, _timeSeries);
				break;                    
			//}
			[Conditional("OBJ_RECTANGLE")] 
			//{
			case OBJ_RECTANGLE:
				mq4Object = new Mq4Rectangle(name, type, _algoChartObjects);
				break;
			//}					
			[Conditional("OBJ_ARROW")] 
			//{
			case OBJ_ARROW:
				mq4Object = new Mq4Arrow(name, type, _algoChartObjects, _timeSeries);
				break;                                        
			//}		
			[Conditional("OBJ_FIBO")] 
			//{
			case OBJ_FIBO:
				mq4Object = new Mq4Fibo(name, type, _algoChartObjects, _timeSeries);
				break;                                        
			//}
		}
		if (mq4Object == null) 
			return;

		_algoChartObjects.RemoveObject(name);
		if (_mq4ObjectByName.ContainsKey(name))
		{
			_mq4ObjectByName.Remove(name);
			_mq4ObjectNameByIndex.Remove(name);
		}
		_mq4ObjectByName[name] = mq4Object;
            
		mq4Object.Set(OBJPROP_TIME1, time1);
		mq4Object.Set(OBJPROP_TIME2, time2);
		mq4Object.Set(OBJPROP_TIME3, time3);
		mq4Object.Set(OBJPROP_PRICE1, price1);
		mq4Object.Set(OBJPROP_PRICE2, price2);
		mq4Object.Set(OBJPROP_PRICE3, price3);

		mq4Object.Draw();
	}
	
	public void Set(string name, int index, Mq4Double value)
	{
		if (!_mq4ObjectByName.ContainsKey(name))
			return;
		_mq4ObjectByName[name].Set(index, value);
		_mq4ObjectByName[name].Draw();
	}

	[Conditional("ObjectGet")] 
	public Mq4Double Get(string name, int index)
	{
		if (!_mq4ObjectByName.ContainsKey(name))
			return 0;

		return _mq4ObjectByName[name].Get(index);
	}
        
	public void SetText(string name, string text, int font_size, string font, int color)
	{
		if (!_mq4ObjectByName.ContainsKey(name))
			return;
		[Conditional("OBJ_TEXT")] 
		//{
		var mq4Text = _mq4ObjectByName[name] as Mq4Text;
		if (mq4Text != null)
			mq4Text.Text = text;
		//}
		[Conditional("OBJ_LABEL")] 
		//{
		var mq4Label = _mq4ObjectByName[name] as Mq4Label;
		if (mq4Label != null)
			mq4Label.Text = text;
		//}

		Set(name, OBJPROP_COLOR, color);
	}

	[Conditional("ObjectDelete", "ObjectsDeleteAll")] 
	public void Delete(string name)
	{
		Mq4Object mq4Object;
		if (!_mq4ObjectByName.TryGetValue(name, out mq4Object))
			return;
		
		mq4Object.Dispose();
		_mq4ObjectByName.Remove(name);
		_mq4ObjectNameByIndex.Remove(name);
	}

	[Conditional("ObjectsDeleteAll")] 
	public int DeleteAll(int type)
	{
		if (type == EMPTY)
		{
			var count = _mq4ObjectByName.Count;
			_algoChartObjects.RemoveAllObjects();
			_mq4ObjectByName.Clear();
			_mq4ObjectNameByIndex.Clear();
			return count;
		}
		var deletedCount = 0;
		foreach (var mq4Object in _mq4ObjectByName.Select(kvp => kvp.Value).ToArray())
		{
			if (mq4Object.Type == type)
			{
				Delete(mq4Object.Name);
				deletedCount++;
			}
		}
		return deletedCount;
	}

	[Conditional("ObjectFind")] 
	public int Find(string name)
	{
		if (_mq4ObjectByName.ContainsKey(name))
			return 0;//index of window
		return -1;
	}

	[Conditional("ObjectMove")] 
	public void Move(string name, int point, int time, double price)
	{
		if (!_mq4ObjectByName.ContainsKey(name))
			return;
		var mq4Object = _mq4ObjectByName[name];
		switch (point)
		{
			case 0:
			mq4Object.Set(OBJPROP_TIME1, time);
			mq4Object.Set(OBJPROP_PRICE1, price);
			break;
			case 1:
			mq4Object.Set(OBJPROP_TIME2, time);
			mq4Object.Set(OBJPROP_PRICE2, price);
			break;          
			case 2:
			mq4Object.Set(OBJPROP_TIME3, time);
			mq4Object.Set(OBJPROP_PRICE3, price);
			break;
		}
	}

	[Conditional("ObjectName")] 
	public string ObjectName(int index)
	{
		if (index <= 0 || index >= _mq4ObjectNameByIndex.Count)
			return string.Empty;

		return _mq4ObjectNameByIndex[index];
	}

	[Conditional("ObjectType")] 
	public int ObjectType(string name)
	{
		if (!_mq4ObjectByName.ContainsKey(name))
			return -1;
		
		var mq4Object = _mq4ObjectByName[name];
		return mq4Object.Type;
	}

	[Conditional("ObjectSetFiboDescription")] 
	public void SetFiboDescription(string name, int index, string text)
	{
		var mq4Fibo = GetObject<Mq4Fibo>(name);
		if (mq4Fibo == null)
			return;

		mq4Fibo.SetLevelDescription(index, text);
	}

	[Conditional("ObjectGetFiboDescription")] 
	public string GetFiboDescription(string name, int index)
	{
		var mq4Fibo = GetObject<Mq4Fibo>(name);
		if (mq4Fibo == null)
			return string.Empty;

		return mq4Fibo.GetLevelDescription(index);
	}

	private T GetObject<T>(string name) where T : Mq4Object
	{
		Mq4Object mq4Object;
		if (!_mq4ObjectByName.TryGetValue(name, out mq4Object))
			return null;
		return mq4Object as T;
	}

	[Conditional("ObjectGetValueByShift", "Mq4TrendLine")] 
	public double ObjectGetValueByShift(string name, int shift)
	{
		var mq4TrendLine = GetObject<Mq4TrendLine>(name);
		if (mq4TrendLine == null)
			return 0;
		
		return mq4TrendLine.GetValueByShift(shift);			
	}

	[Conditional("ObjectDescription")] 
	public string ObjectDescription(Mq4String name)
	{
		if (!_mq4ObjectByName.ContainsKey(name))
			return string.Empty;
		[Conditional("OBJ_TEXT")] 
		//{
		var mq4Text = _mq4ObjectByName[name] as Mq4Text;
		if (mq4Text != null)
			return mq4Text.Text;
		//}
		[Conditional("OBJ_LABEL")] 
		//{
		var mq4Label = _mq4ObjectByName[name] as Mq4Label;
		if (mq4Label != null)
			return mq4Label.Text;
		//}

		return string.Empty;
	}
}
