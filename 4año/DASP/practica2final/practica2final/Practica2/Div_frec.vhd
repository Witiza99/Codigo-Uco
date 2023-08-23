----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    14:20:12 04/07/2021 
-- Design Name: 
-- Module Name:    Div_frec - Behavioral 
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
use IEEE.std_logic_unsigned.all;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity Div_frec is
    Port ( Clk : in  STD_LOGIC;
           reset : in  STD_LOGIC;
           sat : out  STD_LOGIC;
           sat2 : out  STD_LOGIC);
end Div_frec;

architecture Behavioral of Div_frec is

signal contador: std_logic_vector (25 downto 0) := (others=>'0');

begin
	process (Clk, reset)--list de sensibilidad del proceso que indica que el proceso se ejecuta si hay cambios en CLK o reset
	begin 
		if reset='1' then
			contador<="00"&X"000000";
		elsif rising_edge(clk) then 
			contador<=contador+1;
		end if;
	end process;
	sat <='1' when contador="11"&X"FFFFFF" ELSE '0';
	sat2 <='1' when contador(7 downto 0)="11111111" ELSE '0';
end Behavioral;

