----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    10:31:53 03/29/2021 
-- Design Name: 
-- Module Name:    Registro - Behavioral 
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

entity Registro is
    Port ( D : in  bit_vector (3 downto 0);
           S : in  bit_vector (2 downto 0);
           Q : out  bit_vector (3 downto 0);
           CLK : in  std_logic);
end Registro;

architecture Behavioral of Registro is

Signal Contenido: bit_vector (3 downto 0) := (others=>'0');

begin

	process (S, D, CLK)--list de sensibilidad del proceso que indica que el proceso se ejecuta si hay cambios en s, a o b
	
	begin
	
		if rising_edge(clk) then 
	
		case S is
			when "000" =>
			Contenido <= Contenido;
			
			when "001" =>
			Contenido <= Contenido srl 2;
			
			when "010" =>
			Contenido <= "0000";
			
			when "011" =>
			for i in 0 to 3 loop
				Contenido(i) <= D(i);
			end loop;
			
			when "100" =>
			Contenido <= not(Contenido);
			
			when "101" =>
			Contenido <= D and Contenido;
			
			when "110" =>
			Contenido <= D or Contenido;
			
			when "111" =>	
			Contenido <= Contenido rol 1;
			
			when others =>
			Contenido <= Contenido;
			
		end case;
		
		end if;
	end process;
	
	Q <= Contenido;
	
end Behavioral;