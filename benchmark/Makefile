all:
	@./run ../anywhere-concurrent 8000
	@./run ../anywhere-iterative 8001
	@./run ../anywhere-multithread 8002
	@killall -m anywhere # kill all process which name matches `anywhere`
