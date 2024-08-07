main()
{
	char   vc, *pc;		// char 型の通常変数と char 型へのポインタ
	int    vi, *pi;		// int 型の通常変数と int 型へのポインタ
	double vd, *pd;		// double 型の通常変数と double 型へのポインタ

	printf("［通常変数のデータサイズ］\n");
	printf("sizeof(vc)  = %d\n", sizeof(vc));
	printf("sizeof(vi)  = %d\n", sizeof(vi));
	printf("sizeof(vd)  = %d\n", sizeof(vd));
	printf("\n");

	printf("［ポインタのデータサイズ］\n");
	printf("sizeof(pc)  = %d\n", sizeof(pc));
	printf("sizeof(pi)  = %d\n", sizeof(pi));
	printf("sizeof(pd)  = %d\n", sizeof(pd));
	printf("\n");

	printf("［ポインタの参照先のデータサイズ］\n");
	printf("sizeof(*pc) = %d\n", sizeof(*pc));
	printf("sizeof(*pi) = %d\n", sizeof(*pi));
	printf("sizeof(*pd) = %d\n", sizeof(*pd));
}
