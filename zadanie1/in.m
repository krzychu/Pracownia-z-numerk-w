#! /usr/bin/octave -q
A = [ 
   5.12317,    1.26761,    4.39311,    1.03864,    5.62034,     9.3152,    2.17453, ;
   1.27025,    6.84311,   0.593039,    2.35175,    2.76148,    8.18753,    2.62001, ;
  0.154032,    4.53731,    6.71288,    7.55077,    7.77539,    3.71655,   0.941143, ;
   9.97104,    2.87108,    3.61894,    1.40557,    4.89575,    6.23416,    3.56744, ;
   2.27007,    1.94499,    3.92815,    7.39325,     3.2126,    8.32126,    8.43189, ;
   8.83294,    7.63646,   0.606416,   0.103189,    4.47957,    1.19946,    2.45494, ;
   7.24105,    9.38698,    5.07495,    7.39508,    3.92429,    1.78783,    4.94585, ;
]
;B = [ 
   1.69968,    5.50438,    5.88699,    1.67072,    8.37545,    9.50594,    3.07629, ;
    3.2712,     5.7401,    6.64373,    5.54127,    7.68509,   0.571877,    2.93452, ;
  0.897692,    8.89313,    1.36641,    9.73063,    6.52959,    1.97283,    9.83382, ;
   1.00916,    3.17228,    2.28876,     8.2502,    2.55926,    7.36371,    5.64528, ;
   6.48355,    9.15154,   0.591134,    8.18323,    4.65591,    6.47813,    9.85395, ;
   3.03137,    5.98406,    2.93024,    6.30257,    1.72416,    9.57397,    1.84385, ;
   9.40925,   0.145847,    4.77837,    0.30694,    9.03898,    6.14478,  0.0375728, ;
]
;C_fast = [ 
   102.984,    185.334,    87.9706,     172.27,    145.878,    204.695,    141.185, ;
   94.8258,    133.655,    97.2778,    140.219,    123.776,    146.852,    85.5035, ;
   99.2841,    204.078,    77.4897,    240.356,    150.433,    164.639,    205.935, ;
   115.213,    190.637,    124.144,    159.828,    198.593,    227.238,    142.493, ;
     146.6,    162.472,    115.148,    195.112,    184.051,    237.174,    140.373, ;
   96.4207,    146.705,    121.692,    108.796,    182.005,    145.876,    102.573, ;
   132.432,    209.664,    160.044,    219.406,    250.909,    211.598,    183.627, ;
]
;C_std = [ 
   102.984,    185.334,    87.9706,     172.27,    145.878,    204.695,    141.185, ;
   94.8258,    133.655,    97.2778,    140.219,    123.776,    146.852,    85.5035, ;
   99.2841,    204.078,    77.4897,    240.356,    150.433,    164.639,    205.935, ;
   115.213,    190.637,    124.144,    159.828,    198.593,    227.238,    142.493, ;
     146.6,    162.472,    115.148,    195.112,    184.051,    237.174,    140.373, ;
   96.4207,    146.705,    121.692,    108.796,    182.005,    145.876,    102.573, ;
   132.432,    209.664,    160.044,    219.406,    250.909,    211.598,    183.627, ;
]
;printf("fast error matrix\n");
A * B - C_fast
printf("slow error matrix\n");
A * B - C_std
printf("identity squared fast\n");
D = [ 
         1,          0,          0,          0,          0,          0,          0, ;
         0,          1,          0,          0,          0,          0,          0, ;
         0,          0,          1,          0,          0,          0,          0, ;
         0,          0,          0,          1,          0,          0,          0, ;
         0,          0,          0,          0,          1,          0,          0, ;
         0,          0,          0,          0,          0,          1,          0, ;
         0,          0,          0,          0,          0,          0,          1, ;
]
