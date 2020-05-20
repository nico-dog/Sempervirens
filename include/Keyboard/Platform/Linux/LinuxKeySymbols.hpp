#ifndef LINUXKEYSYMBOLS_HPP
#define LINUXKEYSYMBOLS_HPP

#define XK_LATIN1
#include <X11/keysymdef.h>
#include <X11/XKBlib.h>

namespace sempervirens::keyboard
{
  using Keysym = KeySym;
  using Keychr = char*;

#define KEY_SPACE XK_space 
#define KEY_EXCLA XK_exclam                    
#define KEY_QUOTE XK_quotedbl                  
#define KEY_POUND XK_numbersign                
#define KEY_USDLR XK_dollar                    
#define KEY_PRCNT XK_percent                   
#define KEY_AMPSD XK_ampersand                 
#define KEY_APOST XK_apostrophe                
#define KEY_QUOTR XK_quoteright                
#define KEY_PARNL XK_parenleft                 
#define KEY_PARNR XK_parenright                
#define KEY_ASTER XK_asterisk                  
#define KEY_PLUS XK_plus                      
#define KEY_COMM XK_comma                     
#define KEY_MINUS XK_minus                     
#define KEY_POINT XK_period                    
#define KEY_SLASH XK_slash                     
#define KEY_0 XK_0                         
#define KEY_1 XK_1                         
#define KEY_2 XK_2                         
#define KEY_3 XK_3                         
#define KEY_4 XK_4                         
#define KEY_5 XK_5                         
#define KEY_6 XK_6                         
#define KEY_7 XK_7                         
#define KEY_8 XK_8                         
#define KEY_9 XK_9                         
#define KEY_COLON XK_colon                     
#define KEY_SEMIC XK_semicolon                 
#define KEY_LESS XK_less                      
#define KEY_EQUAL XK_equal                     
#define KEY_GREAT XK_greater                   
#define KEY_QUEST XK_question                  
#define KEY_AT XK_at                        
#define KEY_A XK_A                         
#define KEY_B XK_B                         
#define KEY_C XK_C                         
#define KEY_D XK_D                         
#define KEY_E XK_E                         
#define KEY_F XK_F                         
#define KEY_G XK_G                         
#define KEY_H XK_H                         
#define KEY_I XK_I                         
#define KEY_J XK_J                         
#define KEY_K XK_K                         
#define KEY_L XK_L                         
#define KEY_M XK_M                         
#define KEY_N XK_N                         
#define KEY_O XK_O                         
#define KEY_P XK_P                         
#define KEY_Q XK_Q                         
#define KEY_R XK_R                         
#define KEY_S XK_S                         
#define KEY_T XK_T                         
#define KEY_U XK_U                         
#define KEY_V XK_V                         
#define KEY_W XK_W                         
#define KEY_X XK_X                         
#define KEY_Y XK_Y                         
#define KEY_Z XK_Z                         
#define KEY_BRACL XK_bracketleft               
#define KEY_BKSLA XK_backslash                 
#define KEY_BRACR XK_bracketright              
#define KEY_CIRCM XK_asciicircum               
#define KEY_UNDER XK_underscore                
#define KEY_GRAVE XK_grave                     
#define KEY_QUOTL XK_quoteleft                 
#define KEY_a XK_a                         
#define KEY_b XK_b                         
#define KEY_c XK_c                         
#define KEY_d XK_d                         
#define KEY_e XK_e                         
#define KEY_f XK_f                         
#define KEY_g XK_g                         
#define KEY_h XK_h                         
#define KEY_i XK_i                         
#define KEY_j XK_j                         
#define KEY_k XK_k                         
#define KEY_l XK_l                         
#define KEY_m XK_m                         
#define KEY_n XK_n                         
#define KEY_o XK_o                         
#define KEY_p XK_p                         
#define KEY_q XK_q                         
#define KEY_r XK_r                         
#define KEY_s XK_s                         
#define KEY_t XK_t                         
#define KEY_u XK_u                         
#define KEY_v XK_v                         
#define KEY_w XK_w                         
#define KEY_x XK_x                         
#define KEY_y XK_y                         
#define KEY_z XK_z                         
#define KEY_CURLL XK_braceleft                 
#define KEY_BAR XK_bar                       
#define KEY_CURLR XK_braceright                
#define KEY_TILDE XK_asciitilde                
}
#endif
