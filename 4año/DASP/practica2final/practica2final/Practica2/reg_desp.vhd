----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    13:15:40 04/21/2021 
-- Design Name: 
-- Module Name:    reg_desp - Behavioral 
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

entity reg_desp is
    Port ( Clk : in  STD_LOGIC;
           reset : in  STD_LOGIC;
           enable : in  STD_LOGIC;
           display_enable : out  bit_vector (3 downto 0));
end reg_desp;

architecture Behavioral of reg_desp is

signal contador: bit_vector (3 downto 0) := "1110";
begin
process (Clk, reset, enable)--list de sensibilidad del proceso que indica que el proceso se ejecuta si hay cambios en CLK o reset
	begin 
		if reset='1' then
			contador<="1110";
		elsif rising_edge(clk) then 
			contador <= contador rol 1;
		end if;
	end process;

display_enable <= contador;

end Behavioral;

