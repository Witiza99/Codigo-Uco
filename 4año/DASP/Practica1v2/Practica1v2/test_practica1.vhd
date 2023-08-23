--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   12:02:21 03/29/2021
-- Design Name:   
-- Module Name:   E:/xinlinx/Practica1/test_practica1.vhd
-- Project Name:  Practica1
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: Registro
-- 
-- Dependencies:
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
-- Notes: 
-- This testbench has been automatically generated using types std_logic and
-- std_logic_vector for the ports of the unit under test.  Xilinx recommends
-- that these types always be used for the top-level I/O of a design in order
-- to guarantee that the testbench will bind correctly to the post-implementation 
-- simulation model.
--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY test_practica1 IS
END test_practica1;
 
ARCHITECTURE behavior OF test_practica1 IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT Registro
    PORT(
         D : IN  bit_vector(3 downto 0);
         S : IN  bit_vector(2 downto 0);
         Q : OUT  bit_vector(3 downto 0);
         CLK : IN  std_logic
        );
    END COMPONENT;
    

   --Inputs
   signal D : bit_vector(3 downto 0) := (others => '0');
   signal S : bit_vector(2 downto 0) := (others => '0');
   signal CLK : std_logic := '0';

 	--Outputs
   signal Q : bit_vector(3 downto 0);

   -- Clock period definitions
   constant CLK_period : time := 100 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: Registro PORT MAP (
          D => D,
          S => S,
          Q => Q,
          CLK => CLK
        );

   -- Clock process definitions
   CLK_process :process
   begin
		CLK <= '0';
		wait for CLK_period;
		CLK <= '1';
		wait for CLK_period;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin		
      S <= "010";
		D <= "0000";
      wait for 200 ns;
		
		S <= "000";
		D <= "0001";
      wait for 200 ns;
		
		S <= "011";
		D <= "0100";
      wait for 200 ns;
		
		S <= "001";
		D <= "0100";
      wait for 200 ns;	
		
		S <= "001";
		D <= "0101";
      wait for 200 ns;
		
		S <= "100";
		D <= "0101";
      wait for 200 ns;	
		
		S <= "101";
		D <= "0101";
      wait for 200 ns;
		
		S <= "110";
		D <= "0101";
      wait for 200 ns;
		
		S <= "111";
		D <= "0101";
      wait for 200 ns;
		
      wait;
   end process;

END;
