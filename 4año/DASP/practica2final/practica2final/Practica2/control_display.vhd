----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    13:26:30 04/21/2021 
-- Design Name: 
-- Module Name:    control_display - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity control_display is
    Port ( Clk : in  STD_LOGIC;
           reset : in  STD_LOGIC;
           led : out  STD_LOGIC_VECTOR (6 downto 0);
           dp : out  STD_LOGIC;
           an : out  bit_vector (3 downto 0));
end control_display;


architecture Behavioral of control_display is
	Component Div_frec is
		 Port ( Clk : in  STD_LOGIC;
				  reset : in  STD_LOGIC;
				  sat : out  STD_LOGIC;
				  sat2 : out  STD_LOGIC);
	End component Div_frec;

	Component cont_digito is
		 Port ( Clk : in  STD_LOGIC;
				  reset : in  STD_LOGIC;
				  enable : in  STD_LOGIC;
				  cuenta : out  STD_LOGIC_VECTOR (3 downto 0);
				  sat : out  STD_LOGIC);
	End component cont_digito;

	Component decodificador is
		 Port ( binario : in  STD_LOGIC_VECTOR (3 downto 0);
				  led : out  STD_LOGIC_VECTOR (6 downto 0));
	End component decodificador;

	Component reg_desp is
		 Port ( Clk : in  STD_LOGIC;
				  reset : in  STD_LOGIC;
				  enable : in  STD_LOGIC;
				  display_enable : out  bit_vector (3 downto 0));
	End Component reg_desp;

	Signal sat, sat2, satcont_dig1, satcont_dig2, satcont_dig3, satcont_dig4, sat0y1, sat1y2, sat2y3 : STD_LOGIC;
	Signal cuenta1, cuenta2, cuenta3, cuenta4, binario : STD_LOGIC_VECTOR (3 downto 0);
	Signal display_enable :  bit_vector (3 downto 0);
	Signal led_dec :  STD_LOGIC_VECTOR (6 downto 0);

	begin

		UDiv_frec : Div_frec port map(Clk, reset, sat, sat2);
		U1cont_digito : cont_digito port map(Clk, reset, sat, cuenta1, satcont_dig1);
		sat0y1 <= sat and satcont_dig1;
		U2cont_digito : cont_digito port map(Clk, reset, sat0y1, cuenta2, satcont_dig2);
		sat1y2 <= sat0y1 and satcont_dig2;
		U3cont_digito : cont_digito port map(Clk, reset, sat1y2, cuenta3, satcont_dig3);
		sat2y3 <= sat1y2 and satcont_dig3;
		U4cont_digito : cont_digito port map(Clk, reset, sat2y3, cuenta4, satcont_dig4);
		Ureg_desp : reg_desp port map(Clk, reset, sat2, display_enable);
		
		with display_enable select
			binario <= 	cuenta1 when "1110",
							cuenta2 when "1101",
							cuenta3 when "1011",
							cuenta4 when others;
		Udecodificador : decodificador port map(binario, led_dec);
		
		led <= led_dec;
		dp <= '1';
		an <= display_enable;

end Behavioral;

