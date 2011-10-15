
function print_mat(file, mat) 
	[w,h] = size(mat);
	fprintf(file, "%d %d\n", w,h);
	for i = 1:h
		for j = 1:w
			fprintf(file, "%20.10g", mat(i,j))
		endfor
		fprintf(file, "\n");
	endfor
endfunction

function gen_matrix(suffix, dim)
	A = rand(dim);
	A_inv = inv(A);
	
	filename = sprintf("mat_%d_%s.mat", dim, suffix)
	file = fopen(filename, "w");
	print_mat(file, A);
	fclose(file);

	filename = sprintf("inv_%d_%s.mat", dim, suffix)
	file = fopen(filename, "w");
	print_mat(file, A_inv);
	fclose(file);

endfunction


for s = 1:10:101
	gen_matrix("", s);	
endfor
