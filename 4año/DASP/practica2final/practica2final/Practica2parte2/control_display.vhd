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
           an : out  bit_vector (3 downto 0);
			  up : in STD_LOGIC;
			  dw : in STD_LOGIC;
			  l_up : out STD_LOGIC;
			  l_dw : out STD_LOGIC);
end control_display;


architecture Behavioral of control_display is
	Component Div_frec is
		 Port ( Clk : in  STD_LOGIC;
				  reset : in  STD_LOGIC;
				  sat : out  STD_LOGIC;
				  sat2 : out  STD_LOGIC);
	End component Div_frec;

	Component cont_digito is
		 Port ( 	Clk : in  STD_LOGIC;
					reset : in  STD_LOGIC;
					enable : in  STD_LOGIC;
					up : in STD_LOGIC;
					dw : in STD_LOGIC;
					cuenta : out  STD_LOGIC_VECTOR (3 downto 0));
	End component cont_digito;

	Component decodificador is
		 Port ( binario : in  STD_LOGIC_VECTOR (3 downto 0);
				  led : out  STD_LOGIC_VECTOR (6 downto 0));
	End component decodificador;


	Signal sat, sat2 : STD_LOGIC;
	Signal cuenta1 : STD_LOGIC_VECTOR (3 downto 0);
	Signal display_enable :  bit_vector (3 downto 0);
	Signal led_dec :  STD_LOGIC_VECTOR (6 downto 0);

	begin

		UDiv_frec : Div_frec port map(Clk, reset, sat, sat2);
		Ucont_digito : cont_digito port map(Clk, reset, up, dw, sat, cuenta1);
		auxiliar <= sat and satcont_dig1;
		
		Ureg_desp : reg_desp port map(Clk, reset, sat2, display_enable);

		Udecodificador : decodificador port map(cuenta1, led_dec);
		
		led <= led_dec;
		dp <= '1';
		an <= "0111";
		l_up <= up;
		l_dw <= l_dw;
		
		

end Behavioral;

