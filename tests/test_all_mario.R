source("tests/create_test_lib.R")

create_LIB(lib_name="LIB_test", total_sigs=1000, seed_sig_csv="tests/LINCSCP_1000.tsv")

library(iLincsCor)
# lib <- new(iLincsCor,"data/LIB_test/")
lib <- new(iLincsCor,"/Users/medvedm/tmp/ilincscor/data/LIB_5/")
vec <- lib$read_input("tests/LINCSCP_1000.tsv")
for(i in 2:20){
x<-bench::mark(cor_vec <-lib$cor(vec,4))
print(x)
}
cat("Result: ")
cat(lib$signature_names[which(cor_vec>0.9)])
cat("\n")

