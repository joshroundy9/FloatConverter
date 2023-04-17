This was a project for my System Fundimentals class in the final semester of sophomore year. <br />
The program is executed by ./project2 [number of randoms to generate] [file extension to be used for the four files]. 
Then the specified amount of random numbers (-100.0 to +100.0) will be generated, converted to IEEE754 format, <br />
converted back and finally compared to the original number.

Then depending on the value of the generated number the following will be written to one of four files: <br />
66.180122 (Original generated number) <br />
NEGATIVE: [ 0 ] EXPONENT: [ 1 0 0 0 0 1 0 1 ] MANTISSA: [ 1 0 0 0 0 1 0 0 0 1 0 1 1 1 0 0 0 0 1 1 1 0 0 1 ] (IEEE754 floating point format) <br />
66.180122 (Number generated from converting the IEEE754 back to float) <br />

The four files will hold values: neg(-100.0 to -1.0) neg_frac(-0.99... to 0) pos_frac(0 to 0.99..) and pos(1.0 to 100.0) <br />

Making this project taught me the pros, cons and differences of single and double precision floats and a lot more about how numbers are generally stored in memory.
