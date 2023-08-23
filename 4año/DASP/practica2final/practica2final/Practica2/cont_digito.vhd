----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    13:31:39 04/14/2021 
-- Design Name: 
-- Module Name:    cont_digito - Behavioral 
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

entity cont_digito is
    Port ( Clk : in  STD_LOGIC;
           reset : in  STD_LOGIC;
           enable : in  STD_LOGIC;
           cuenta : out  STD_LOGIC_VECTOR (3 downto 0);
           sat : out  STD_LOGIC);
end cont_digito;

architecture Behavioral of cont_digito is
signal contador: std_logic_vector (3 downto 0) := (others=>'0');
begin
process (Clk, reset, enable)--list de sensibilidad del proceso que indica que el proceso se ejecuta si hay cambios en CLK o reset
	begin 
		if reset='1' then 
			contador<="0000";
		elsif enable = '1' and rising_edge(clk) then 
			contador<=contador+1;
			if contador="1001" then
				contador<="0000";
			end if;
		end if;
	end process;
sat <='1' when contador="1001" ELSE '0';
end Behavioral;

