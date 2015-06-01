__author__ = 'ashley'

def makeUnique (seq, idfun=None):
	"""Returns a copy of seq with all duplicates removed. order preserving"""
	if idfun is None:
		def idfun(x): return x
	seen = {}
	result = []
	for item in seq:
		marker = idfun (item)
		if marker in seen: continue
		seen[marker] = 1
		result.append (item)
	return result


if __name__ == "__main__":
	a = [1, 2, 3, 3, 3, 4, 5, 5, 5, 6, 7, 8, 8, 8, 8, 8, 9, 0, 0]
	b = [{'a': 'a', 'b': 'b'}, {'a': 'foo', 'b': 'bar'}, {'a': 'a', 'b': 'bar'}, {'a': 'foo', 'b': 'bar'}]
	c = makeUnique (a)
	d = makeUnique (b, lambda x: x['a'])
	print ('a: ', a)
	print ('b: ', b)
	print ('c: ', c)
	print ('d: ', d)